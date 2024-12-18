

template <typename E>
class Textura {
    public:
    virtual E sample(const double u, const double v, const Punto& p) const = 0;
};