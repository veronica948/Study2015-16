// npclient.cpp: определяет точку входа для консольного приложения.
//


//***************************************************************
// From the book "Win32 System Services: The Heart of Windows NT"
// by Marshall Brain
// Published by Prentice Hall
//
// Copyright 1994, by Prentice Hall.
//
// This code implements a simple named pipe sender.
//***************************************************************


// Usage: ssnpsend

#include "stdafx.h"

#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
  char *toSendtxt="Veronica";
  HANDLE ssnpPipe;
  DWORD NumBytesWritten;
  char machineName[80];
  char pipeName[80];

  cout <<  "Enter name of server machine: ";
  cin >> machineName;
  wsprintfA(pipeName, "\\\\%s\\pipe\\ssnp",
    machineName);

  /* Create the named pipe file handle for sending
     messages */
  ssnpPipe=CreateFileA(pipeName,
    GENERIC_WRITE, FILE_SHARE_READ,
    (LPSECURITY_ATTRIBUTES) NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
    (HANDLE) NULL);

  /* Check and see if the named pipe file was
     opened, if not terminate program */
  if (ssnpPipe == INVALID_HANDLE_VALUE)
  {
    cerr <<  "ERROR: Unable to create a named pipe "
      <<  endl;
    cerr <<  GetLastError() <<  endl;
    return (1);
  }

  /* Repeatedly send message until program is
     terminated */
  while(1)
  {
    cout <<  "Sending..." <<  endl;
    /* Write message to the pipe */
    if (!WriteFile(ssnpPipe,
          toSendtxt, (DWORD) strlen(toSendtxt)+1,
          &NumBytesWritten, (LPOVERLAPPED) NULL))
    {
      /* If error occurs when writing to named
         pipe, terminate program */
      cerr <<  "ERROR: Unable to write to named pipe "
        <<  GetLastError() <<  endl;
      CloseHandle(ssnpPipe);
      return (1);
    }

    /* Wait before sending the message again */
    Sleep(4800);
  } /* while*/
}


