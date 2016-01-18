# CinemaSimulator
Projet réalisé lors de l'UV LO41 (Systèmes d'exploitation, principes et communication) dispensée à l'UTBM. 
Ce projet est une simulation de vente de billets dans un cinema. le clients achètent un billet puis ils se rendent dans la salle afin de regarder le film. Une fois le film teriné, ils sortent du cinema. Les abonnés sont prioritaires au près des caissières mais pas au autres types de paiement.
Les salles sont gérées dynamiquement ainsi si un film est refusé un certain nombre de fois, une nouvelle salle est réouverte (si possible).

#Compilation

il suffit simple de faire Make

#execution

Il suffit d'executer le fichier bin/cinemaSimulator :
cd bin ; ./cinemaSimulator

#Configuration (optionelle)

Il suffit de modifier le fichier config.xml pour changer le nombre de client, de salles, de caisses.
On peut aussi modifier les films, les salles et beaucoup d'autres parametres.
