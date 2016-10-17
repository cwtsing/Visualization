#include "db/material_lib.h"
#include <QDebug>

MaterialLib* MaterialLib::mInstance;
const QString MaterialLib::CREATE_MATERIAL_TABLE_SQL = "CREATE TABLE material_table ("
                                           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "name VARCHAR NOT NULL "
                                                       "UNIQUE,"
                                           "destiny FLOAT,"
                                           "emissivity FLOAT,"
                                           "type       INTEGER NOT NULL)";
const QString MaterialLib::CREATE_TMPLAMBDA_TABLE_SQL = "CREATE TABLE tmp_lambda_table ("
                                           "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                                           "material    INTEGER REFERENCES material_table (id) ON DELETE RESTRICT "
                                                                                        "ON UPDATE RESTRICT,"
                                           "temperature FLOAT,"
                                           "lambda      FLOAT)";
const QString MaterialLib::CREATE_TMPCP_TABLE_SQL = "CREATE TABLE tmp_cp_table ("
                                            "id         INTEGER PRIMARY KEY AUTOINCREMENT,"
                                            "material   INTEGER REFERENCES material_table (id) ON DELETE RESTRICT "
                                                                                        "ON UPDATE RESTRICT,"
                                            "temperature FLOAT,"
                                            "cp         FLOAT)";


MaterialLib::MaterialLib()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("test.db");
    db.open();

    QSqlQuery query = QSqlQuery(db);
    query.exec(CREATE_MATERIAL_TABLE_SQL);
    query.exec(CREATE_TMPLAMBDA_TABLE_SQL);
    query.exec(CREATE_TMPCP_TABLE_SQL);
}

MaterialLib::~MaterialLib()
{
    if (db.isOpen()) {
        db.close();
    }
}

MaterialLib* MaterialLib::getInstance()
{
    if (mInstance == NULL) {
        mInstance = new MaterialLib();
    }

    return mInstance;

}

MaterialLib::Material* MaterialLib::getMaterial(int index)
{
    Material* material = NULL;

    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT id, name, destiny, emissivity FROM material_table "
                  "WHERE id = " + QString::number(index);

    if (query.exec(sql)) {

        while (query.next()) {
            material = new Material();
            material->id = query.value(0).toInt();
            material->materialName = query.value(1).toString();
            material->destiny = query.value(2).toFloat();
            material->emissivity = query.value(3).toFloat();
        }
    }

    return material;
}

MaterialLib::Material* MaterialLib::getMaterial(const QString& name)
{
    Material* material = NULL;

    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT id, name, destiny, emissivity FROM material_table WHERE name = ?";

    query.prepare(sql);
    query.addBindValue(name);

    if (query.exec()) {

        while (query.next()) {
            material = new Material();
            material->id = query.value(0).toInt();
            material->materialName = query.value(1).toString();
            material->destiny = query.value(2).toFloat();
            material->emissivity = query.value(3).toFloat();
        }
    }

qDebug() << query.lastError();
    return material;
}

QList<MaterialLib::Material> MaterialLib::getMaterialNameList()
{
    QList<MaterialLib::Material> list;

    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT id, name, type FROM material_table ORDER BY type, name";

    if (query.exec(sql)) {
        while (query.next()) {
            Material material;
            material.id = query.value(0).toInt();
            material.materialName = query.value(1).toString();
            material.type = query.value(2).toInt();
            list.append(material);
        }
    }

    return list;
}

int MaterialLib::getIndexOrderByName(int type, const QString& name)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT (SELECT COUNT(*) FROM material_table WHERE name < ? AND type = ?) + 1 AS rownum "
                        " FROM material_table WHERE name = ?";

    query.prepare(sql);
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(name);


    if (query.exec()) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }
qDebug() << query.lastError();
    return -1;
}

bool MaterialLib::addMaterial(const QString& name, int type)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "INSERT INTO material_table (name, type) values(?,?)";

    query.prepare(sql);
    query.addBindValue(name);
    query.addBindValue(type);

    if (query.exec()) {
        return true;
    } else {
        return false;
    }
}

bool MaterialLib::deleteMaterial(int index)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "DELETE FROM material_table WHERE id = ?";

    query.prepare(sql);
    query.addBindValue(index);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << query.lastError();
        return false;
    }
}

bool MaterialLib::isExist(const QString& name)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT name FROM material_table WHERE name = ?";

    query.prepare(sql);
    query.addBindValue(name);

    if (query.exec()) {
        if (query.next()) {
            return true;
        }

        return false;
    } else {
        return false;
    }
}

QMap<float, float> MaterialLib::getTmpLambdaMap(int index)
{
    QMap<float, float> map;

    QSqlQuery query = QSqlQuery(db);;
    QString sql = "SELECT t2.temperature, t2.lambda FROM material_table AS t1 "
                  "JOIN tmp_lambda_table AS t2 ON t1.id = t2.material "
                  "WHERE t1.id = " + QString::number(index);

    if (query.exec(sql)) {
        while (query.next()) {
            map.insert(query.value(0).toFloat(), query.value(1).toFloat());
        }
    }

    return map;
}

QMap<float, float> MaterialLib::getTmpCpMap(int index)
{
    QMap<float, float> map;

    QSqlQuery query = QSqlQuery(db);
    QString sql = "SELECT t2.temperature, t2.cp FROM material_table AS t1 "
                  "JOIN tmp_cp_table AS t2 ON t1.id = t2.material "
                  "WHERE t1.id = " + QString::number(index);

    if (query.exec(sql)) {
        while (query.next()) {
            map.insert(query.value(0).toFloat(), query.value(1).toFloat());
        }
    }

    return map;
}

bool MaterialLib::updateMaterialName(int index, const QString& name)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "UPDATE material_table SET name = ? WHERE id = ?";

    query.prepare(sql);
    query.addBindValue(name);
    query.addBindValue(index);
    if (query.exec()) {
        return true;
    } else {
        return false;
    }
}

bool MaterialLib::updateMaterialProperty(int index, float destiny ,float emissivity)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "UPDATE material_table SET destiny = ?, emissivity = ? WHERE id = ?";

    query.prepare(sql);
    query.addBindValue(destiny);
    query.addBindValue(emissivity);
    query.addBindValue(index);
    if (query.exec()) {
        return true;
    } else {
        return false;
    }
}

bool MaterialLib::updateMaterialTmpLambdaMap(int index, QMap<float, float> tmpLambdaMap)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "DELETE FROM tmp_lambda_table WHERE material = ?";

    query.prepare(sql);
    query.addBindValue(index);

    if (query.exec()) {
        sql = "INSERT INTO tmp_lambda_table (material, temperature, lambda) values(?,?,?)";
        QVariantList temperatures;
        QVariantList lambdas;
        QVariantList ids;
        for (QMap<float,float>::iterator it = tmpLambdaMap.begin();it != tmpLambdaMap.end();it++) {
            temperatures << it.key();
            qDebug() << temperatures;
            lambdas << it.value();
            ids << index;
        }
        query.prepare(sql);
        query.addBindValue(ids);
        query.addBindValue(temperatures);
        query.addBindValue(lambdas);

        if (query.execBatch()) {
            return true;
        } else {
            qDebug() << query.lastError();
            return false;
        }
    } else {
        return false;
    }
}

bool MaterialLib::updateMaterialTmpCpMap(int index, QMap<float, float> tmpCpMap)
{
    QSqlQuery query = QSqlQuery(db);
    QString sql = "DELETE FROM tmp_cp_table WHERE material = ?";

    query.prepare(sql);
    query.addBindValue(index);

    if (query.exec()) {
        sql = "INSERT INTO tmp_cp_table (material, temperature, cp) values(?,?,?)";
        QVariantList temperatures;
        QVariantList cps;
        QVariantList ids;
        for (QMap<float,float>::iterator it = tmpCpMap.begin();it != tmpCpMap.end();it++) {
            temperatures << it.key();
            cps << it.value();
            ids << index;
        }
        query.prepare(sql);
        query.addBindValue(ids);
        query.addBindValue(temperatures);
        query.addBindValue(cps);

        if (query.execBatch()) {
            return true;
        } else {
            qDebug() << query.lastError();
            return false;
        }
    } else {
        return false;
    }
}
