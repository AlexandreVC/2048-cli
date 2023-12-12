#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "engine.h"
#include <libintl.h>
#include <locale.h>

const char *hs_dir_name  = "2048";
const char *hs_file_name = "highscore";

static const char* highscore_retrieve_file(void)
{
    static char buffer[4096];

    if (getenv("XDG_DATA_HOME") != NULL) {
        snprintf(buffer, sizeof(buffer), "%s/%s/%s",
                getenv("XDG_DATA_HOME"), hs_dir_name, hs_file_name);
    }
    else if (getenv("HOME")) {
        snprintf(buffer, sizeof(buffer), "%s/.local/share/%s/%s",
                getenv("HOME"), hs_dir_name, hs_file_name);
    }
    else {
        return hs_file_name;
    }

   char *sep = strrchr(buffer, '/');
while (sep != NULL) {
    *sep = '\0';
    if (strnlen(buffer, sizeof(buffer)) != 0) {
        // Essayez de créer le répertoire
        if (mkdir(buffer, S_IRWXU | S_IRWXG) == -1) {
            // Gérez l'erreur si le répertoire ne peut pas être créé
            if (errno != EXIST) {
                // Gestion des erreurs si le répertoire n'existe pas déjà
                return NULL;
            }
        }
    }
    char *tmpsep = sep;
    sep = strrchr(buffer, '/');
    *tmpsep = '/';
}

// Effectuez maintenant les opérations sur le fichier
FILE *fd = fopen(buffer, "r");
if (!fd) {
    fd = fopen(buffer, "w+");
    if (!fd) {
        // Gestion des erreurs si le fichier ne peut pas être ouvert ou créé
        return NULL;
    }
}
// Fermez le fichier si vous l'avez juste ouvert pour le créer
fclose(fd);

return buffer;

}

static inline void string_to_lower(char *str)
{
    for (; *str; ++str) *str = tolower(*str);
}

void highscore_reset(void)
{
    const char *hsfile = highscore_retrieve_file();
    const size_t resp_length = 16;
    char resp[resp_length];

    printf(gettext("Are you sure you want to reset your scores? Y(es) or N(o)\n"));

    while (1) {
        /* fgets is used to avoid queuing that may occur with getchar */
        if (fgets(resp, resp_length, stdin) == NULL)
            return;

        string_to_lower(resp);

        const size_t sl = strnlen(resp, resp_length);
        if (sl < resp_length)
            resp[sl - 1] = '\0';

        if (!strncmp(resp, gettext("yes"), resp_length) || !strncmp(resp, gettext("y"), resp_length))
            goto reset_scores;
        else if (!strncmp(resp, "no", resp_length) || !strncmp(resp, "n",  resp_length))
            return;

        printf(gettext("Please enter Yes or No\n"));
    }

reset_scores:;
    FILE *fd = fopen(hsfile, "w+");
    fprintf(fd, "%d", 0);
    fclose(fd);
}

long highscore_load(struct gamestate *g)
{
    const char *hsfile = highscore_retrieve_file();
    long result = 0;

    FILE *fd = fopen(hsfile, "r");
    if (fd == NULL)
        fd = fopen(hsfile, "w+");

    if (fd == NULL) {
        fprintf(stderr, gettext("load: Failed to open highscore file\n"));
        return 0;
    }

    if (fscanf(fd, "%ld", &result) != 1) {
        fprintf(stderr, gettext("load: Failed to parse highscore file\n"));
        result = 0;
    }

    fclose(fd);

    if (g) g->score_high = result;
    return result;
}

void highscore_save(struct gamestate *g)
{
    /* Someone could make their own merge rules for highscores and this could be meaningless,
     * howeverhighscores are in plaintext, so that isn't that much of a concern */
    if (g->score < g->score_high || g->opts->grid_width != 4 ||
            g->opts->grid_height != 4 || g->opts->ai == true)
        return;

    const char *hsfile = highscore_retrieve_file();

    FILE *fd = fopen(hsfile, "w");
    if (fd == NULL) {
        fprintf(stderr, gettext("save: Failed to open highscore file\n"));
        return;
    }

    if (fprintf(fd, "%ld", g->score) < 0) {
        fprintf(stderr, gettext("save: Failed to write highscore file\n"));
    }
    fclose(fd);
}
