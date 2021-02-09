#include <stdio.h>
#include <string.h>
#include <gdbm.h>

int
main (int argc, char **argv)
{
  GDBM_FILE gdbf;     /* Database file object pointer */
  datum key, content; /* Key and content data */
  int status = 0;     /* Exit status of the program: 0 - OK, 1 - key
                         not found, 2 - error. */
                       
  /*
   * Validate arguments.
   */
  if (argc != 3)
    {
      fprintf (stderr, "usage: %s DBFILE KEY\n", argv[0]);
      return 2;
    }

  /*
   * Open the database.  The GDBM_READER flag indicates that we only intend
   * to read from it.
   */  
  gdbf = gdbm_open (argv[1], 0, GDBM_READER, 0, NULL);
  if (gdbf == NULL)
    {
      fprintf (stderr, "can't open database: %s\n",
               gdbm_strerror (gdbm_errno));
    }

  /*
   * Prepare the lookup key.  Notice, that the terminating \0 character
   * is not counted in the dsize computation.
   */
  key.dptr = argv[2];
  key.dsize = strlen (argv[2]);

  /*
   * Look up the key in the database.
   */
  content = gdbm_fetch (gdbf, key);

  /*
   * Analyze the return.
   */
  if (content.dptr != NULL)
    {
      /*
       * The key is found.  Print the content on the stdout and
       * indicate success.
       */
      fwrite (content.dptr, content.dsize, 1, stdout);
      putchar ('\n');
      status = 0;
    }
  else if (gdbm_errno == GDBM_ITEM_NOT_FOUND)
    {
      /*
       * There is no such key in the database.
       */
      fprintf (stderr, "no such key\n");
      status = 1;
    }
  else
    {
      /*
       * An error occurred.
       */
      fprintf (stderr, "%s\n", gdbm_db_strerror (gdbf));
      status = 2;
    }

  /*
   * Close the database and return.
   */
  gdbm_close (gdbf);
  return status;
}

