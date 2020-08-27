#include <QApplication>
#include <iostream>
#include <QDateTime>

#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	Model m;
	Controller c(&m);
	View v(&c);
	c.setView(&v);


    //****************************************************************************
/*
    c.createNewProject();
    c.setProjectName("p1");

    c.createNewProject("p2");

    c.deleteProject(1);
    c.setActiveProject(0);

    unsigned short int l1 = m.addNewList();
    unsigned short int l2 = m.addNewList();
    c.setListName(l1,"lista1");
    c.setListName(l2,"lista2");

    QStringList info;

    //*****************************************************************

    unsigned short int t0 = m.addNewTask(l1);
    t0 = m.convertToContainer(l1,t0);
    info.push_back("t0_l1");
    info.push_back("ccccc");
    c.aggiornaTask(l1,t0,info);

    unsigned short int t1 = m.addNewTaskChild(l1,t0);
    unsigned short int t2 = m.addNewTaskChild(l1,t0);

    info.clear();
    info = m.getTaskInfo(l1,t0);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;

    info.clear();
    std::cout<<std::endl;

    //*****************************************************************

    //unsigned short int t1 = m.addNewTask(l1);
    info.push_back("t1_l1");
    info.push_back("aaaaa");
    c.aggiornaTask(l1,t1,info);

    info.clear();

    info = m.getTaskInfo(l1,t1);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;

    info.clear();
    std::cout<<std::endl;

    //******************************************************************

    //unsigned short int t2 = m.addNewTask(l1);
    t2 = m.convertToPriority(l1,t2);
    info.push_back("t2_l1");
    info.push_back("bbbbb");
    QDateTime date = QDateTime::fromString("03.09.2020 10:18:00","dd.MM.yyyy hh:mm:ss");
    info.push_back(date.toString("dd.MM.yyyy hh:mm:ss"));
    c.aggiornaTask(l1,t2,info);
    info.clear();
    info = m.getTaskInfo(l1,t2);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;

    info.clear();
    std::cout<<std::endl;

    //*****************************************************************

    t0 = m.convertToPriority(l1,t0);
    info.push_back("t0_l1");
    info.push_back("ccccc");
    date = QDateTime::fromString("11.09.2020 11:11:00","dd.MM.yyyy hh:mm:ss");
    info.push_back(date.toString("dd.MM.yyyy hh:mm:ss"));
    c.aggiornaTask(l1,t0,info);

    info.clear();
    info = m.getTaskInfo(l1,t0);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;

    info.clear();
    std::cout<<std::endl;

    //*******************************************************************

    c.dragAndDrop(l1,l2,t0);

    info.clear();
    info = m.getTaskInfo(l2,t0);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;
    std::cout<<std::endl;

    info.clear();
    info = m.getTaskInfo(l2,t1);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;
    std::cout<<std::endl;

    info.clear();
    info = m.getTaskInfo(l2,t2);
    for(int i=0; i<info.size(); ++i)
        std::cout<< info.at(i).toStdString() <<std::endl;
    std::cout<<std::endl;

    std::cout<<"banana"<<std::endl;
*/
//*****************************************************************************

//	Controller c;
//	TextHolder v("prova");
//	TaskWidget v;
//	TaskPreview v;
//	TaskHolder v;
//	TasksListWidget v("Prova");
//	TasksList v;
//	DragDrop v;
//	ProjectView v;
//	View v;

    v.show();
    return app.exec();
}

