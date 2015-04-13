//
// Created by pochemuto on 13.04.15.
//

#ifndef MATERIALSOLVER_DATABASE_H
#define MATERIALSOLVER_DATABASE_H

#include <vector>
#include "sqlite3pp/sqlite3pp.h"
#include "Material.h"
#include "Polynomial.h"

class Database {
    sqlite3pp::database db;

    void createSchema();
    void createTable(char const* schema);
public:
    Database(char const* fileName):db(fileName) {
        createSchema();
    }

    long storeConfiguration(std::vector<Layer> layers, double t, double tN);

    void storeFunctionT(int cid, std::vector<Polynomial> functions);

    void storeFunctionV(int cid, std::vector<Polynomial> functions);
};


#endif //MATERIALSOLVER_DATABASE_H
