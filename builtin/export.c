#include "minishell.h"

/*
- si pas d'argument (argc == 1)
affichage des variables (voir diff avec env  : export au début de chaque ligne + 
“” autour de la value + ordre alphabetique de key : voir avec strcmp pour ordre d'impression)

- si 1 argument (ne contient pas de '=')
export NOMVARIABLE → la variable sera exportee dans tous les childs process 
(exemple : possibilite de faire echo $NOMVARIABLE apres 
avoir lance export NOMVARIABLE puis bash)
si elle n'existe pas il la cree sans valeur
n'affiche rien

- si 1 argument (contient un egal) 
creation d’une nouvelle variable (ex : export HOLA=bonjour) 
ou changement de la VALUE si la variable existait deja
n'affiche rien

- si plusieurs arguments, traire successivemet chaque arguments selon les regles ci-dessus 
en fonction de la presence de = ou pas

-identifiant valide : lettres ou chifres ou _, pas autre chose 
memes regles d'extension des $x que pour le parsing sauf qu'il ne doit pas rester de $ dans le nom
(ex : $x entre ' ' -> nom invalide, $x entre "" -> OK)

- memes regles d'extension des $ que pour le parsing, sauf ' + $ -> \$...

- doit-on gerer export truc+=chose ? 
qui vient ajouter chose a la valeur deja d2finie avant
*/

int ft_export(t_cmd cmd)
{
    return (0);
}