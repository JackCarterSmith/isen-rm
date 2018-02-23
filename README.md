# ISEN Repair Monitor
## Cahier des charges
### Exigences
- Pouvoir stocker des 'fiches' PC, comprennant l'ID (unique), un nom à titre indicatif, le type de processeur, la quantité de mémoire vive (RAM), la capacité de stockage du disque dur, le système d'exploitation ainsi que les étapes de validation de bon fonctionnement de l'ordinateur (Hardware, OS, pilotes, software).
- Affichage de divers compteur (PC réparés totaux depuis le début de l'année, PC prêts pour livraison, etc...).
- Enregistrement des évènements dans des logs (ajout, suppression, modification, validation, etc...).
- Backup des données journalière.

### Functions
#### Public
- Compteur de PC totaux réparés.
#### Internes
- Compteur de PC prêts à être expédiés.
- Log des entrées et sorties des PC.
- Backup manuelle de la BD.

### Type d'accès
- Technicien : Peut modifier les fiches PC à l'intérieur de la BD.
- Responsable inventaire : Peut ajouter les nouveaux PC à restaurés dans la BD et association d'une fiche vierge pour chacun d'entre eux.
- Validateur : Valide le fonctionnement d'un PC, il a le choix entre renvoyer le PC en atelier ou approuver son bon fonctionnement et le préparer pour une livraison.

## Guide d'utilisation
### Constitution
Le logiciel est composé d'un seul fichier executable, lors de la première utilisation il n'y a que ce fichier, lors des executions suivantes un fichier `db.irm` sera présent dans le dossier ainsi qu'un ou plusieurs fichiers `yyyy-mm-dd.log`.

Le fichier `db.irm` correspond à la base de donnée, celui-ci peut être copier/déplacer/remplacer manuellement par l'utilisateur s'il souhaite gérer lui même ses sauvegardes.

Les fichiers `yyyy-mm-dd.log` correspondent aux entrées de log. Le log enregistre toutes les activités de manipulation de la base de donnée ainsi que des détails sur les erreurs si elles viennent à se produire.

### Menu connexion et général
Il y a 2 menus principaux dans l'application, le premier sert à renseigner l'identifiant utilisateur afin que l'application sache à qui elle s'adresse (simple visiteur, technicien, responsable,...).

Préciser seulement à cet écran votre identifiant à **8 chiffres et lettres** puis appuyer sur **entrer**.

Vous accéder ensuite au menu principal correspondant à votre niveau d'autorisation.

### Détails des fonctions à venir...
...

## Function implémenté
### v1.0
- Menu utilisateur personalisé
- Moteur DB
- Ajout fiche pc
- Suppression fiche pc
- Edition fiche pc
- Ajout compteurs de suivis
- Système de log des actions

## TODO
- Remove bugs and SEGF...
