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


    Material(double const k, double const E, double const v, double const a) : k(k),
                                                                                               E(E),
                                                                                               l(LAME(E,v)),
                                                                                               v(v),
                                                                                               a(a) { }

    /*
     * Рассчитывает коэффициент Ламе через модуль Юнга E и коэффициент Пуассона v
     */
    static double LAME(const double E, const double v) {
        return v * E / (1 + v) / (1 - 2 * v);
    }
};

struct Layer : Material {
    double y;
    Layer(const Material mat, double y) : Material(mat), y(y) {}
};

#endif //MATERIALSOLVER_MATERIAL_H
