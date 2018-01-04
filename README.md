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

## Function implémenté
### v1.0
- Moteur DB
- Système de log des actions

## TODO
- Conception du menu principal
- Construction des functions publique et compteur
- Début des batteries de tests et optimisation du code (si possible)
