/*
 * PROJECT:     ReactOS Run-Time Library
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     ANSI Prefix handling implementation support
 * COPYRIGHT:   Copyright 2021 George Bișoc <george.bisoc@reactos.org>
 */

/* INCLUDES *******************************************************************/

#include <rtl.h>
//#define NDEBUG
#include <debug.h>

/* DEFINES ********************************************************************/

typedef USHORT NODE_TYPE_CODE;
#define PFX_NTC_ANSI_TABLE ((NODE_TYPE_CODE)0x0200)
#define PFX_NTC_ANSI_ROOT ((NODE_TYPE_CODE)0x0201)
#define PFX_NTC_ANSI_CHILD ((NODE_TYPE_CODE)0x0202)

/* FUNCTIONS ******************************************************************/

static
ULONG
ComputeNameLengthFromString(
    _In_ PSTRING AnsiName)
{
    ULONG i, Characters, NamesFound;
    PAGED_CODE_RTL();

    DPRINT("ComputeNameLengthFromString() function called (string buffer -> %s)\n", AnsiName->Buffer);

    NamesFound = 0;
    Characters = AnsiName->Length / sizeof(CHAR);

    /* Does the system support multi-byte code page? */
    if (NlsMbCodePageTag)
    {
        /*
         * FIXME: On Windows Server 2003 SP2 the function checks if NLS multi-byte code page
         * is detected on the system. And if that is the case Windows uses NlsLeadByteInfoTable
         * exported variable that this code path depends on it. Since we don't have such table
         * I'd rather not want to implement hacks as I'd vomit blood if I see hacks. This should
         * be left as is until there will be a time when it'll be implemented with proper code.
         */
        UNIMPLEMENTED;
        ASSERT(FALSE);
    }
    else
    {
        /*
         * The system is on a single-byte code page,
         * loop over the string to gather the names.
         */
        for (i = 0; i < (Characters - 1); i++)
        {
            /* If we found a backslash that means we found a name */
            if (AnsiName->Buffer[i] == '\\')
            {
                NamesFound++;
            }
        }
    }

    /* Return the total number of names we found */
    return NamesFound;
}

static
RTL_GENERIC_COMPARE_RESULTS
CompareNamesCaseSensitiveFromStrings(
    _In_ PSTRING Prefix,
    _In_ PSTRING String)
{

}

VOID
NTAPI
PfxInitialize(
    _Inout_ PPREFIX_TABLE PrefixTable)
{
    PAGED_CODE_RTL();

    DPRINT("PfxInitialize() function called (table -> %p)\n", PrefixTable);

    /* Set up the table */
    PrefixTable->NodeTypeCode = PFX_NTC_ANSI_TABLE;
    PrefixTable->NameLength = 0;
    PrefixTable->NextPrefixTree = (PPREFIX_TABLE_ENTRY)PrefixTable;
}

BOOLEAN
NTAPI
PfxInsertPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING Prefix,
    _Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry)
{
    UNIMPLEMENTED;
    return FALSE;
}

VOID
NTAPI
PfxRemovePrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PPREFIX_TABLE_ENTRY PrefixTableEntry)
{
    UNIMPLEMENTED;
}

PPREFIX_TABLE_ENTRY
NTAPI
PfxFindPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING FullName)
{
    UNIMPLEMENTED;
    return NULL;
}
