#ifndef MATERIAL_LIB_H
#define MATERIAL_LIB_H
#include <QFile>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QHash>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class MaterialLib
{

public:

    class Material;
    static MaterialLib *getInstance();
    QList<Material> getMaterialNameList();
    QMap<float, float> getTmpLambdaMap(int index);
    QMap<float, float> getTmpCpMap(int index);
    Material* getMaterial(int index);
    Material* getMaterial(const QString& name);
    int getIndexOrderByName(int type, const QString& name);
    bool addMaterial(const QString& name, int type);
    bool deleteMaterial(int index);
    bool isExist(const QString& name);
    bool updateMaterialName(int index, const QString &name);
    bool updateMaterialProperty(int index, float destiny ,float emissivity);
    bool updateMaterialTmpLambdaMap(int index, QMap<float, float> tmpLambdaMap);
    bool updateMaterialTmpCpMap(int index, QMap<float, float> tmpCpMap);

    class Material {
    public:
        int id;
        QString materialName;
        float destiny;
        float emissivity;
        int type;
    };


private:
    MaterialLib();
    ~MaterialLib();
    const static QString CREATE_MATERIAL_TABLE_SQL;
    const static QString CREATE_TMPLAMBDA_TABLE_SQL;
    const static QString CREATE_TMPCP_TABLE_SQL;
    static MaterialLib *mInstance;
    QSqlDatabase db;
};

#endif // MATERIAL_LIB_H
