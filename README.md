# Liberty

## Abstract

Applicazione per la gestione di progetti, ispirata alla web app trello.com, sviluppata per il progetto di Programmazione ad Oggetti 2019/2020

## Progettazione e descrizione delle gerarchie usate

## Descrizione delle chiamate polimorfe

## Descrizione I/O

## Ambiente di sviluppo

## Manuale utente

## Suddivisione dei compiti e tempistiche

### Segnali e slot

Creazione Task: 
passare std:pair<unsigned short, TaskType>
- TaskListWidget: void getTasksIds(const unsigned short)->
- ProjectView: onGetTasksIds(const unsigned short listId)...getTasksIds(const unsigned short, const unsigned short)->
- Controller: onGetTasksIds(const unsigned short, const unsigned short)...sendTasksIds(const unsigned short, const unsigned short, std::vector<unsigned short, TaskType>)->
- ProjectView: fetchTasksIds(const unsigned short, const unsigned short, std::vector<unsigned short, TaskType)...sendTasksIds(const unsigned short, std::vector<unsigned short, TaskType>)->
- TaskListWidget: fetchTasksIds(const unsigned short, std::vector<unsigned short, TaskType>) >> TaskPreview(const unsigned short)

- TaskPreview: getTaskName(const unsigned short)->
- TaskListWidget: onGetTaskName(const unsigned short)...getTaskName(const unsigned short, const unsigned short)->
- ProjectView: onGetTaskName(const unsigned short, const unsigned short)...getTaskName(const unsigned short, const unsigned short, const unsigned short)->
- Controller: onGetTaskName(const unsigned short, const unsigned short, const unsigned short)...sendTaskName(const unsigned short, const unsigned short, const unsigned short, const QString&)->
- ProjectView: onSendTaskName(const unsigned short, const unsigned short, const unsigned short, const QString&)...sendTaskName(const unsigned short, const unsigned short, const QString&)->
- TaskListWidget: onSendTaskName(const unsigned short, const unsigned short, const QString&)...sendTaskName(const unsigned short, const QString&)->
- TaskPreview: fetchTaskName(const unsigned short, const QString&)


Apertura task
- TaskPreview: getTaskInfo(const unsigned short)->
- TaskListWidget: onGetTaskInfo(const unsigned short)...getTaskInfo(const unsigned short, const unsigned short)->
- ProjectView: onGetTaskInfo(const unsigned short, const unsigned short)...getTaskInfo(const unsigned short, const unsigned short, const unsigned short)->
- Controller: onGetTaskInfo(const unsigned short, const unsigned short, const unsigned short)...sendTaskInfo(const unsigned short, const unsigned short, const unsigned short, QStringList)->
- ProjectView: onSendTaskInfo(const unsigned short, const unsigned short, const unsigned short, QStringList)...sendTaskInfo(const unsigned short, const unsigned short, QStringList)->
- TaskListWidget: onSendTaskInfo(const unsigned short, const unsigned short, QStringList)...sendTaskInfo(const unsigned short, QStringList)->
- TaskPreview: 
