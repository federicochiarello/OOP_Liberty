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
- Controller: onGetTasksIds(const unsigned short, const unsigned short)...sendTasksIds(const unsigned short, const unsigned short, std::vector<unsigned short>)->
- ProjectView: fetchTasksIds(const unsigned short, const unsigned short, std::vector<unsigned short)...sendTasksIds(const unsigned short, std::vector<unsigned short>)->
- TaskListWidget: fetchTasksIds(const unsigned short, std::vector<unsigned short>) >> TaskPreview()
