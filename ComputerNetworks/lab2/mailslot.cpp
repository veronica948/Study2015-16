// mailslot.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;


/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}*/

#include <windows.h>
#include <iostream>

int main()
{
  char toDisptxt[80];
  HANDLE hSMS_Slot;
  DWORD nextSize;
  DWORD Msgs;
  DWORD NumBytesRead;
  BOOL Status;

  /* Create a mailslot for receiving messages */
  hSMS_Slot=CreateMailslot(TEXT("\\\\.\\mailslot\\sms"),
    0, 0, (LPSECURITY_ATTRIBUTES) NULL);

  /* Check and see if the mailslot was created */
  if (hSMS_Slot == INVALID_HANDLE_VALUE)
  {
    cerr <<  "ERROR: Unable to create mailslot "
      <<  GetLastError() <<  endl;
    return (1);
  }

  /* Repeatedly check for messages until the
     program is terminated */
  while(1)
  {
    Status=GetMailslotInfo(hSMS_Slot,
      (LPDWORD) NULL, &nextSize, &Msgs,
      (LPDWORD) NULL);
    if (!Status)
    {
      cerr <<  "ERROR: Unable to get status. "
        <<  GetLastError() <<  endl;
      CloseHandle(hSMS_Slot);
      return (1);
    }

    /* If messages are available, then get them */
    if (Msgs)
    {

      /* Read the message and check to see if
         read was successful */
      if (!ReadFile(hSMS_Slot, toDisptxt, nextSize,
        &NumBytesRead, (LPOVERLAPPED) NULL))
      {
        cerr
          <<  "ERROR: Unable to read from mailslot "
          <<  GetLastError() <<  endl;
        CloseHandle(hSMS_Slot);
        return (1);
      }

      /* Display the Message */
      cout <<  toDisptxt <<  endl;
    }
    else
      /* Check for new messages twice a second */
      Sleep(500);
  } /* while */
}


