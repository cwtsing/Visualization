#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T14:11:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualization
TEMPLATE = app
include(utils/utils.pri)
include(mywidget/mywidget.pri)
include(db/db.pri)

SOURCES += main.cpp\
    widget_main.cpp \
    widget_heatec.cpp \
    widget_hcd.cpp \
    widget_wind_tunnel.cpp \
    widget_ihcp.cpp \
    widget_cal_ball_head.cpp \
    widget_cal_cylinder.cpp \
    widget_flight.cpp \
    widget_atmosphere_model.cpp \
    widget_ihcp_1.cpp \
    widget_ihcp_2.cpp \
    dialog_material_lib.cpp \
    widget_choose.cpp \
    dialog_login.cpp \
    widget_flat.cpp \
    widget_mulpoint.cpp \
    dialog_table.cpp \
    dialog_temperature.cpp


HEADERS  += \
    widget_heatec.h \
    widget_hcd.h \
    widget_main.h \
    widget_wind_tunnel.h \
    widget_ihcp.h \
    widget_cal_ball_head.h \
    widget_cal_cylinder.h \
    widget_flight.h \
    widget_atmosphere_model.h \
    dialog_material_lib.h \
    widget_ihcp_1.h \
    widget_ihcp_2.h \
    widget_chooset.h \
    dialog_login.h \
    common.h \
    widget_flat.h \
    widget_mulpoint.h \
    dialog_table.h \
    dialog_temperature.h


FORMS    +=

STATECHARTS +=

RESOURCES +=

DISTFILES +=
