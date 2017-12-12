#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"
#include <QTimer>

#include <QList>
#include "QEntity.h"

#include <QLabel>
// qlabel inclut les textes masi aussi les images
// sans le .h, inclut toutes les dépendances
// parfois c'est la même chose mais parfois ce n'est pas la même chose...

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	~QtGuiApplication1();
	size_t x{ 500 };
	size_t y{ 500 };
private:
	Ui::QtGuiApplication1Class ui;

	QSize mSceneSize;
	QLabel * mScene; // on va mettre notre dessin dedans

	QTimer mTimer; // connecter le timer sur une slot

	QList<QEntity*>mEntities;

	void paint();

private slots:
	void tic();
};
