#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wlanapi.h>

#pragma comment(lib, "wlanapi.lib")

void list_networks() {
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = 0;
    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    PWLAN_AVAILABLE_NETWORK_LIST pNetworkList = NULL;

    // Open a handle to the WLAN client
    dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) {
        printf("WlanOpenHandle failed with error: %lu\n", dwResult);
        return;
    }

    // Enumerate wireless interfaces
    dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        printf("WlanEnumInterfaces failed with error: %lu\n", dwResult);
        WlanCloseHandle(hClient, NULL);
        return;
    }

    if (pIfList->dwNumberOfItems == 0) {
        printf("No wireless interfaces found\n");
        WlanFreeMemory(pIfList);
        WlanCloseHandle(hClient, NULL);
        return;
    }

    printf("Found %lu wireless interface(s):\n", pIfList->dwNumberOfItems);
    
    for (DWORD i = 0; i < pIfList->dwNumberOfItems; i++) {
        const WLAN_INTERFACE_INFO* pIfInfo = &pIfList->InterfaceInfo[i];
        printf("Interface %lu: %ws\n", i, pIfInfo->strInterfaceDescription);
        
        // Get available networks for this interface
        dwResult = WlanGetAvailableNetworkList(hClient, 
                                              &pIfInfo->InterfaceGuid, 
                                              0, 
                                              NULL, 
                                              &pNetworkList);
        
        if (dwResult != ERROR_SUCCESS) {
            printf("WlanGetAvailableNetworkList failed with error: %lu\n", dwResult);
            continue;
        }

        printf("Available networks (%lu):\n", pNetworkList->dwNumberOfItems);
        
        for (DWORD j = 0; j < pNetworkList->dwNumberOfItems; j++) {
            const WLAN_AVAILABLE_NETWORK* pNetwork = &pNetworkList->Network[j];
            
            printf("  SSID: %-32s", pNetwork->dot11Ssid.ucSSID);
            printf("Signal: %3ld%%", pNetwork->wlanSignalQuality);
            printf("  Security: ");
            
            if (pNetwork->bSecurityEnabled) {
                printf("Enabled");
            } else {
                printf("Open");
            }
            
            printf("\n");
        }
        
        WlanFreeMemory(pNetworkList);
        pNetworkList = NULL;
    }

    // Cleanup
    if (pNetworkList != NULL) {
        WlanFreeMemory(pNetworkList);
    }
    WlanFreeMemory(pIfList);
    WlanCloseHandle(hClient, NULL);
}

int main() {
    printf("Scanning for available Wi-Fi networks...\n");
    list_networks();
    return 0;
}
