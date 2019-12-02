#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// Function thingies for sub menus


int MainMenu(void);

void Sound(void);

void Queueing(void);

void Phonebook(void);

void Testing(void);

// Function thingies for wrapper functions

void DisplayAddress(void);

char* RecordAudio(void);
int Playback(void);
void SoundSettings(void);
void RecordText(void);
void DeleteText(void);
void SendText(void);
void ChangeAddress(void);
int TestRecord(void);
int TestPlayback(void);
void TestRS232(void);
void TransmitMessage(void);



// Constants for changing



