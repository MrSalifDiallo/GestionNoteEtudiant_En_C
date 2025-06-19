# 🎓 GestionNoteEtudiant_En_C

Un projet en **C** pour gérer les notes d’un groupe d’étudiants : saisie, calcul de moyennes, tri et affichage. Inspiré de travaux académiques, ce programme tourne en ligne de commande.

---

## 📁 Structure du dépôt

```
GestionNoteEtudiant_En_C/
│
├── src/
│ ├── main.c # Interface principale : menu CLI, gestion des choix utilisateur
│ ├── etudiant.c # Fonctions de gestion des étudiants (ajout, suppression, lecture)
│ ├── notes.c # Fonctions pour gérer les notes (saisie, calculs)
│ └── utils.c # Fonctions utilitaires (tri, affichage formaté, etc.)
│
├── include/
│ ├── etudiant.h # Déclarations relatives aux étudiants
│ ├── notes.h # Déclarations des fonctions de gestion des notes
│ └── utils.h # Déclarations des utilitaires
│
├── data/ # (Optionnel) fichiers de données (ex. notes.txt, etudiants.txt)
│
├── build/ # (Optionnel) objets compilés, exécutable final
│
├── .gitignore # Pour ignorer les fichiers temporaires, compiles, etc.
└── README.md # Ce fichier
```


---

## 💡 Fonctionnalités principales

- Ajout et suppression d’étudiants avec leurs identifiants
- Saisie des notes (contrôle, examen) pour chaque étudiant
- Calcul de moyenne générale ou pondérée
- Affichage de tous les élèves avec leurs moyennes
- Tri des étudiants selon la moyenne (croissant/décroissant)
- Sauvegarde/lecture des données depuis fichiers textuels

---

## ⚙️ Compilation et exécution

1. **Cloner** le dépôt  
   ```bash
   git clone https://github.com/MrSalifDiallo/GestionNoteEtudiant_En_C.git
   cd GestionNoteEtudiant_En_C
   ```
2. **Compiler avec GCC** :
   ```bash
     gcc -Iinclude -o gestion_notes src/*.c
    ````
3. **Lancer l’application :**
  ```bash
  ./gestion_notes
  ```
Tu seras guidé·e par un menu pour gérer les étudiants et les notes.

---

## 💡 Contribution

1. Fork le projet 
2. Créer une branche pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request
---
## 👤 Auteur

**Salif Diallo**  
💼 Développeur && passionné par les solutions de gestion  
📧 [salifdiallo@esp.sn](mailto:salifdiallo@esp.sn)  
🔗 [GitHub - MrSalifDiallo](https://github.com/MrSalifDiallo)  
🌍 Basé à Dakar, Sénégal
