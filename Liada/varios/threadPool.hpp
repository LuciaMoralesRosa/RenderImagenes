#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

/**
 * @brief Generic tarea queue.
 * 
 * @tparam TipoTarea The tarea type.
 * @tparam TipoResultado The resultado type.
 * @tparam N The number of hilos
 */
template <typename TipoTarea, typename TipoResultado>
class Threadpool {
    private:
        bool parar;
        std::condition_variable esperarColaTareas, esperarColaResultados;
        std::mutex tareaMtx, resultadoMtx;

        std::queue<TipoTarea> colaTareas;
        std::queue<TipoResultado> colaResultados;

        /**
         * @brief Run the tarea loop.
         * This operation runs on every worker thread, and waits for tareas to be enqueued
         * in the tarea queue.
         * 
         * The tarea will run in parallel, and its resultado will be enqueued to the resultado queue.
         * @param i The thread id (for debug purposes)
         */
        void bucleEjecutarTarea(int i) {
            for ( ;; ) {
                // Pop tarea from tarea queue or stop
                TipoTarea tarea;
                {
                    std::unique_lock<std::mutex> lck(tareaMtx);

                    // wait until the tarea queue isn't empty or if the tarea loop should stop
                    esperarColaTareas.wait(lck, [this] {
                        return !colaTareas.empty() || parar;
                    });

                    if (parar) {
                        return;
                    }

                    tarea = colaTareas.front();
                    colaTareas.pop();
                }

                // perform tarea
                TipoResultado resultado = tarea();

                {
                    std::unique_lock<std::mutex> lck(resultadoMtx);
                    colaResultados.push(resultado);
                    
                    // notify resultado in resultado queue
                    esperarColaResultados.notify_one();
                }
            }
        };

    public:
        // Thread array
        std::vector<std::thread> hilos;


        /**
         * @brief Construct a new Threadpool object
         * Initializes the pool of hilos and runs the tarea loop
         */
        Threadpool(unsigned int numHilos) : parar(false) {
            for (unsigned int i = 0; i < numHilos; i++) {
                hilos.push_back(std::thread(&Threadpool::bucleEjecutarTarea, this, i));
            }
        }

        /**
         * @brief Enqueue a tarea and notify any free thread.
         * This operation is mutually exclusive with any other operation that
         * reads/modifies the tarea queue.
         * 
         * @param tarea The tarea to enqueue.
         */
        void encolarTarea(const TipoTarea& tarea) {
            std::unique_lock<std::mutex> lck(tareaMtx);
            colaTareas.push(tarea);
            esperarColaTareas.notify_one();
        }

        /**
         * @brief Pop a resultado from the resultado queue.
         * If the queue is empty, this operation is blocking until a resultado is added
         * into the queue.
         * 
         * @return TipoResultado 
         */
        TipoResultado getResultado() {
            std::unique_lock<std::mutex> lck(resultadoMtx);
            // wait until the resultado queue isn't empty
            esperarColaResultados.wait(lck, [this] {
                return !colaResultados.empty();
            });

            auto val = colaResultados.front();
            colaResultados.pop();
            return val;
        }

        /**
         * @brief Destroy the Threadpool object
         * This will instruct every thread to stop.
         */
        ~Threadpool() {
            {
                std::unique_lock<std::mutex> lck(tareaMtx);
                parar = true;
                
                // notify every thread
                esperarColaTareas.notify_all();
            }

            for (std::thread& hilosActivos : hilos) {
                // controlled termination
                hilosActivos.join();
            }
        }
};