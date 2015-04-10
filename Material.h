//
// Created by pochemuto on 06.04.15.
//

#ifndef MATERIALSOLVER_MATERIAL_H
#define MATERIALSOLVER_MATERIAL_H


struct Material {
    double k;   // коэффициент теплопроводности
    double E;   // модуль Юнга
    double l;   // коэффициент Ламе
    double v;   // коэффициент Пуассона
    double a;   // коэффициент температурного расширения
    double mu;  // модуль сдвига
    double K;   // объемный модуль


    Material(double const k, double const E, double const v, double const a) : k(k),
                                                                               E(E),
                                                                               l(calcLAME(E,v)),
                                                                               v(v),
                                                                               a(a),
                                                                               mu(calcMU(E,v)),
                                                                               K(calcK(E,v)){ }

    /*
     * Рассчитывает коэффициент Ламе через модуль Юнга E и коэффициент Пуассона v
     */
    static double calcLAME(const double E, const double v) {
        return v * E / (1 + v) / (1 - 2 * v);
    }

    /**
     * Модуль сдвига, G
     */
    static double calcMU(const double E, const double v) {
        return E / 2 / (1 + v);
    }

    static double calcK(const double E, const double v) {
        return E / 3 / (1 - 2 * v);
    }
};

struct Layer : Material {
    double y;
    Layer(const Material mat, double y) : Material(mat), y(y) {}
};

#endif //MATERIALSOLVER_MATERIAL_H
