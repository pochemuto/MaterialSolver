//
// Created by pochemuto on 13.04.15.
//

#ifndef MATERIALSOLVER_DATABASE_H
#define MATERIALSOLVER_DATABASE_H

#include <vector>
#include "sqlite3pp/sqlite3pp.h"
#include "struct/Material.h"
#include "struct/Polynomial.h"

using namespace std;

class Database {
    sqlite3pp::database db;

    void createSchema();
    void createTable(string schema);
    void createPolynomTable(string table);
    void storeFunction(int cid, vector<Polynomial> functions, string table);
public:

    Database(char const* fileName):db(fileName) {
        createSchema();
    }

    long storeConfiguration(vector<Layer> layers, double t, double tN);

    void storeFunctionT(int cid, vector<Polynomial> functions);

    void storeFunctionV(int cid, vector<Polynomial> functions);

    void storeFunctionSigmaX(int cid, vector<Polynomial> functions);
};


#endif //MATERIALSOLVER_DATABASE_H
