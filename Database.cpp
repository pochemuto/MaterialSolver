//
// Created by pochemuto on 13.04.15.
//

#include "Database.h"
#include "struct/Polynomial.h"
#include <iostream>

using namespace std;

void Database::createSchema() {
    createTable("CREATE TABLE IF NOT EXISTS layer ("
                       " lid INTEGER PRIMARY KEY AUTOINCREMENT,"
                       " lnum INTEGER NOT NULL,"
                       " mid INTEGER NOT NULL,"
                       " cid INTEGER NOT NULL,"
                       " thickness DOUBLE NOT NULL)");

    createTable("CREATE TABLE IF NOT EXISTS conf ("
                       " cid INTEGER PRIMARY KEY AUTOINCREMENT,"
                       " t DOUBLE,"
                       " tN DOUBLE,"
                       " date DATETIME DEFAULT CURRENT_TIMESTAMP)");

    createPolynomTable("t_func");
    createPolynomTable("v_func");
    createPolynomTable("sx_func");

}


void Database::createPolynomTable(string table) {
    string query("CREATE TABLE IF NOT EXISTS ");
    query += table;
    query += " ("
             " cid INTEGER NOT NULL,"
             " lnum INTEGER NOT NULL,"
             " c1 DOUBLE,"
             " c2 DOUBLE,"
             " c3 DOUBLE)";
    createTable(query);
}

void Database::createTable(string schema) {
    int code;
    code = db.execute(schema.c_str());

    if (code) {
        cerr << db.error_msg() << endl;
    }
}


long Database::storeConfiguration(std::vector<Layer> layers, double t, double tN) {
    sqlite3pp::command st(db, "INSERT INTO conf (t, tN) VALUES (:t, :tN)");
    st.bind(":t", t);
    st.bind(":tN", tN);
    if (st.execute()) {
        cerr << db.error_msg() << endl;
        return -1;
    }

    long long int cid = db.last_insert_rowid();
    int lnum = 0;
    for (auto layer : layers) {
        sqlite3pp::command insert(db, "INSERT INTO layer (cid, lnum, mid, thickness) VALUES (:cid, :lnum, :mid, :thickness)");
        insert.bind(":lnum", lnum);
        insert.bind(":cid", cid);
        insert.bind(":mid", layer.k); // используем коэффициент теплопроводности как ижентификатор материала
        insert.bind(":thickness", layer.y);
        insert.execute();
        lnum++;
    }

    return cid;
}

void Database::storeFunctionT(int cid, vector<Polynomial> functions) {
    storeFunction(cid, functions, "t_func");
}

void Database::storeFunctionV(int cid, vector<Polynomial> functions) {
    storeFunction(cid, functions, "v_func");
}

void Database::storeFunctionSigmaX(int cid, vector<Polynomial> functions) {
    storeFunction(cid, functions, "sx_func");
}

void Database::storeFunction(int cid, vector<Polynomial> functions, string table) {
    int lnum = 0;
    string query("INSERT INTO ");
    query += table;
    query += " (cid, lnum, c1, c2, c3) VALUES (:cid, :lnum, :c1, :c2, :c3)";
    for (auto p : functions) {
        sqlite3pp::command st(db, query.c_str());
        st.bind(":cid", cid);
        st.bind(":lnum", lnum++);
        st.bind(":c1", p.C1);
        st.bind(":c2", p.C2);
        st.bind(":c3", p.C3);
        st.execute();
    }
}
