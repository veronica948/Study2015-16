// client.cpp: определяет точку входа для консольного приложения.
//

// sms_send10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//***************************************************************
// From the book "Win32 System Services: The Heart of Windows NT"
// by Marshall Brain
// Published by Prentice Hall
//
// This code implements a simple mailslot sender.
//***************************************************************

// sms_send.c

// Usage: sms_send

using namespace std;

#include <windows.h>
#include <iostream>
#include <string.h>

int main()
{
  char toSendTxt[100], buffer[100];
  DWORD bufferLen=100;
  HANDLE hSMS_Slot;
  BOOL Status;
  DWORD NumBytesWritten;

  /* Create the mailslot file handle for
     sending messages */
  hSMS_Slot=CreateFile(TEXT ("\\\\mmf410-5\\mailslot\\sms"),
    GENERIC_WRITE, FILE_SHARE_READ,
    (LPSECURITY_ATTRIBUTES) NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    (HANDLE) NULL);

  /* Check and see if the mailslot file was
     opened, if not terminate program */
  if (hSMS_Slot == INVALID_HANDLE_VALUE)
  {
    cerr <<  "ERROR: Unable to create mailslot "
      <<  GetLastError() <<  endl;
    return (1);
  }

  /* form string to send */
  GetComputerNameA(buffer, &bufferLen);
  strcpy_s(toSendTxt, "Veronica from ");
  strcat_s(toSendTxt, buffer);

  /* Repeatedly send message until program
     is terminated */
  while(1)
  {
    cout <<  "Sending..." <<  endl;
    /* Write message to mailslot */
    Status=WriteFile(hSMS_Slot,
      toSendTxt, (DWORD) strlen(toSendTxt)+1,
      &NumBytesWritten, (LPOVERLAPPED) NULL);

    /* If error occurs when writing to mailslot,
       terminate program */
    if (!Status)
    {
      cerr <<  "ERROR: Unable to write to mailslot "
        <<  GetLastError() <<  endl;
      CloseHandle(hSMS_Slot);
      return (1);
    }

    /* Wait sending the message again */
    Sleep(4800);
  } /* while*/
}



