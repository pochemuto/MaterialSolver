//
// Created by pochemuto on 13.04.15.
//

#ifndef MATERIALSOLVER_DATABASE_H
#define MATERIALSOLVER_DATABASE_H

#include <vector>
#include "sqlite3pp/sqlite3pp.h"
#include "Material.h"

class Database {
    sqlite3pp::database db;

    void createSchema();
    void createTable(char const* schema);
public:
    Database(char const* fileName):db(fileName) {
        createSchema();
    }

    long storeConfiguration(std::vector<Layer> layers, double t, double tN);
};


#endif //MATERIALSOLVER_DATABASE_H
