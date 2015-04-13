//
// Created by pochemuto on 13.04.15.
//

#include "Database.h"
#include <iostream>

using namespace std;

void Database::createSchema() {
    createTable("CREATE TABLE IF NOT EXISTS layer ("
                       " lid INTEGER PRIMARY KEY AUTOINCREMENT,"
                       " mid INTEGER NOT NULL,"
                       " cid INTEGER NOT NULL,"
                       " thickness DOUBLE NOT NULL)");

    createTable("CREATE TABLE IF NOT EXISTS conf ("
                       " cid INTEGER PRIMARY KEY AUTOINCREMENT,"
                       " t DOUBLE,"
                       " tN DOUBLE,"
                       " date DATETIME DEFAULT CURRENT_TIMESTAMP)");

    createTable("CREATE TABLE IF NOT EXISTS t_func ("
                       " lid INTEGER NOT NULL,"
                       " c1 DOUBLE,"
                       " c2 DOUBLE)");

    createTable("CREATE TABLE IF NOT EXISTS v_func ("
                       " lid INTEGER NUL NULL,"
                       " c1 DOUBLE,"
                       " c2 DOUBLE,"
                       " c3 DOUBLE)");

}

void Database::createTable(char const* schema) {
    int code;
    code = db.execute(schema);

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
    for (auto layer : layers) {
        sqlite3pp::command insert(db, "INSERT INTO layer (cid, mid, thickness) VALUES (:cid, :mid, :thickness)");
        insert.bind(":cid", cid);
        insert.bind(":mid", layer.k); // используем коэффициент теплопроводности как ижентификатор материала
        insert.bind(":thickness", layer.y);
        insert.execute();
    }

    return cid;
}