#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T14:11:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualization
TEMPLATE = app


SOURCES += main.cpp\
    widget_main.cpp \
    widget_heatec.cpp \
    widget_hcd.cpp \
    widget_wind_tunnel.cpp \
    widget_ihcp.cpp \
    utils.cpp \
    my_treewidget_item.cpp \
    widget_cal_ball_head.cpp \
    widget_cal_cylinder.cpp \
    my_usual_radiobox.cpp \
    widget_flight.cpp \
    widget_atmosphere_model.cpp \
    widget_ihcp_1.cpp \
    widget_ihcp_2.cpp \
    dialog_material_lib.cpp \
    widget_choose.cpp \
    dialog_login.cpp \
    material_lib.cpp \
    generaleditbox.cpp \
    widget_flat.cpp \
    widget_mulpoint.cpp \
    dialog_table.cpp \
    my_combobox_group.cpp

HEADERS  += \
    widget_heatec.h \
    widget_hcd.h \
    widget_main.h \
    widget_wind_tunnel.h \
    widget_ihcp.h \
    utils.h \
    my_treewidget_item.h \
    widget_cal_ball_head.h \
    widget_cal_cylinder.h \
    my_usual_radiobox.h \
    widget_flight.h \
    widget_atmosphere_model.h \
    dialog_material_lib.h \
    widget_ihcp_1.h \
    widget_ihcp_2.h \
    widget_chooset.h \
    dialog_login.h \
    common.h \
    material_lib.h \
    generaleditbox.h \
    widget_flat.h \
    widget_mulpoint.h \
    dialog_table.h \
    my_combobox_group.h

FORMS    += \
    widget_wind_tunnel.ui \
    widget_atmosphere_model.ui

STATECHARTS +=

RESOURCES +=

DISTFILES +=
