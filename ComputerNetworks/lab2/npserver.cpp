// npserver.cpp: определяет точку входа для консольного приложения.
//


//***************************************************************
// From the book "Win32 System Services: The Heart of Windows NT"
// by Marshall Brain
// Published by Prentice Hall
//
// This code implements a simple named pipe server (receiver).
//***************************************************************

// npserver.cpp

// Usage: ssnprecv

#include "stdafx.h"

#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
  char toDisptxt[80];
  HANDLE ssnpPipe;
  DWORD NumBytesRead;

  /* Create a named pipe for receiving messages */
  ssnpPipe=CreateNamedPipe(TEXT ("\\\\.\\pipe\\ssnp"),
    PIPE_ACCESS_INBOUND,
    PIPE_TYPE_MESSAGE | PIPE_WAIT,
    1, 0, 0, 150,
    (LPSECURITY_ATTRIBUTES) NULL);

  /* Check and see if the named pipe was created */
  if (ssnpPipe == INVALID_HANDLE_VALUE)
  {
    cerr <<  "ERROR: Unable to create a named pipe. "
      <<  endl;
    return (1);
  }

  /* Allow a client to connect to the name pipe,
     terminate if unsuccessful */
  cout <<  "Waiting for connection... " <<  endl;
  if(!ConnectNamedPipe(ssnpPipe,
    (LPOVERLAPPED) NULL))
  {
    cerr <<  "ERROR: Unable to connect a named pipe "
      <<  GetLastError() <<  endl;
    CloseHandle(ssnpPipe);
    return (1);
  }

  /* Repeatedly check for messages until the program
     is terminated */
  while(1)
  {
    /* Read the message and check to see if read
       was successful */
    if (!ReadFile(ssnpPipe, toDisptxt,
      sizeof(toDisptxt),
      &NumBytesRead, (LPOVERLAPPED) NULL))
    {
      cerr
        <<  "ERROR: Unable to read from named pipe "
        <<  GetLastError() <<  endl;
      CloseHandle(ssnpPipe);
      return (1);
    }

    /* Display the Message */
    cout <<  toDisptxt <<  endl;

  } /* while */
}


