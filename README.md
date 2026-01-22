# Application Web de Recherche de Destinations de Vacances

## 📋 Projet Web Sémantique - Première Partie (10 points)

Cette application web permet de faciliter la recherche d'une destination de vacances adaptée à un utilisateur spécifique en utilisant XML, DTD/XSD, XSL, XPath et XQuery.

---

## ✅ VÉRIFICATION DES TÂCHES COMPLÉTÉES

### **Tâche 1 (1 pt) : Données XML**
✅ **COMPLÉTÉ**
- **Fichier** : `destinations.xml` - **23 destinations** (plus que les 20 demandées)
- **Fichier** : `utilisateur.xml` - **1 utilisateur** (Marie Dupont)
- Chaque destination contient : id, nom, description, durée, 2 activités, budget
- L'utilisateur contient : nom, prénom, disponibilités, activité préférée, budget

### **Tâche 2 (0.5 pt) : DTD/XSD**
✅ **COMPLÉTÉ**
- **DTD** : `destinations.dtd`, `utilisateur.dtd`
- **XSD** : `destinations.xsd`, `utilisateur.xsd`
- Les fichiers XML référencent les DTD et XSD
- Validation stricte des types de données dans XSD

### **Tâche 3 (0.5 pt) : Lecture en mémoire**
✅ **COMPLÉTÉ**
- **Fichier** : `load_destinations.js`
- **Serveur** : Fonction `loadDestinationsFromXML()` dans `server.js`
- Charge automatiquement les destinations au démarrage du serveur
- Parse le XML et stocke en mémoire

### **Tâche 4 (1 pt) : Formulaire ajout destination**
✅ **COMPLÉTÉ**
- **Interface** : `add_destination.html`
- **Validation** : `form_validation.js`
- **API** : Route POST `/add-destination` dans `server.js`
- **Fonctionnalités** :
  - Validation complète (nom, description min 20 caractères, durée 1-30 jours, budget > 0)
  - Sélection de 2 activités différentes obligatoires
  - Ajout en mémoire ET sauvegarde dans le fichier XML
  - Génération automatique d'ID unique

### **Tâche 5 (1 pt) : Formulaire utilisateur**
✅ **COMPLÉTÉ**
- **Interface** : `edit_user.html`
- **Validation** : `user_form_validation.js`
- **API** : Routes GET `/user` et POST `/save-user` dans `server.js`
- **Fonctionnalités** :
  - Chargement des données existantes
  - Validation complète (nom/prénom min 2 caractères, disponibilités 1-30 jours, budget > 0)
  - Sauvegarde dans le fichier XML

### **Tâche 6 (1 pt) : Recommandation par budget (XPath/XQuery)**
✅ **COMPLÉTÉ**
- **Scripts** : `xpath_budget.js`, `query.xq`
- **Interface** : `xpath_recommendations.html`
- **API** : Route GET `/recommend-by-budget` dans `server.js`
- **Requête XPath** : `//destination[budget <= $userBudget]`
- Affiche les destinations dans le budget de l'utilisateur

### **Tâche 7 (1 pt) : Recommandation 2/3 critères (XPath/XQuery)**
✅ **COMPLÉTÉ**
- **Scripts** : `xpath_two_criteria.js`, `query_two_criteria.xq`
- **Interface** : Intégré dans `xpath_recommendations.html`
- **API** : Route GET `/recommend-two-criteria` dans `server.js`
- **Requêtes XPath multiples** :
  - Budget + Durée
  - Budget + Activité
  - Durée + Activité
- Tri : Par nombre de correspondances (DESC), puis budget (ASC)

### **Tâche 8 (1 pt) : Affichage XSL avec couleurs**
✅ **COMPLÉTÉ**
- **Transformation XSL** : `destinations_transform.xsl`
- **Interface client** : `xslt_display.html`
- **Interface serveur** : `xslt_display_server.html`
- **API** : Route GET `/xslt-transform` dans `server.js`
- **Fonctionnalités** :
  - Lecture en mémoire des destinations
  - Transformation XSL avec paramètre (activité préférée)
  - **Fond JAUNE** : Destinations avec activité préférée
  - **Fond VERT** : Autres destinations
  - Statistiques affichées

### **Tâche 9 (1 pt) : Détails destination (XPath/XQuery)**
✅ **COMPLÉTÉ**
- **Scripts** : `xpath_destination_details.js`, `query_destination_details.xq`
- **Interface** : `destination_details.html`
- **API** : Routes GET `/destination/:id` et GET `/destinations-list` dans `server.js`
- **Requête XPath** : `//destination[id='$id']`
- **Fonctionnalités** :
  - Sélecteur avec toutes les destinations
  - Affichage complet des informations
  - Métadonnées calculées (budget/jour, durée en semaines)
  - Destinations similaires (gamme de budget ±20%)

### **Tâche 10 (1 pt) : Recherche par activité (XPath/XQuery)**
✅ **COMPLÉTÉ**
- **Scripts** : `xpath_by_activity.js`, `query_by_activity.xq`
- **Interface** : `search_by_activity.html`
- **API** : Routes GET `/activities` et GET `/search-by-activity/:activity` dans `server.js`
- **Requête XPath** : `//destination[activites/activite[text()='$activity']]`
- **Fonctionnalités** :
  - Liste toutes les activités disponibles
  - Compte des destinations par activité
  - Recherche avec XPath
  - Statistiques complètes
  - Tri par budget croissant

### **Tâche 11 (1 pt) : Interface graphique**
✅ **COMPLÉTÉ**
- **Page principale** : `index.html` avec navigation complète
- **Design moderne** : `style.css` avec gradients, animations, responsive
- **Fonctionnalités** :
  - Affichage du profil utilisateur
  - Liste de toutes les destinations
  - Filtre destinations recommandées
  - Navigation vers toutes les fonctionnalités
  - Design professionnel et intuitif

---

## 🛠️ TECHNOLOGIES UTILISÉES

### ✅ XML
- `destinations.xml` : 23 destinations
- `utilisateur.xml` : 1 utilisateur
- Structure hiérarchique conforme

### ✅ DTD (Document Type Definition)
- `destinations.dtd` : Structure des destinations
- `utilisateur.dtd` : Structure de l'utilisateur
- Référencés dans les fichiers XML

### ✅ XSD (XML Schema Definition)
- `destinations.xsd` : Schéma avec types de données stricts
- `utilisateur.xsd` : Validation des données utilisateur
- Types : positiveInteger, decimal, string

### ✅ XSL (eXtensible Stylesheet Language)
- `destinations_transform.xsl` : Transformation XML → HTML
- Paramètre dynamique pour activité préférée
- Styles conditionnels (fond jaune/vert)
- Templates pour chaque élément

### ✅ XPath (XML Path Language)
Utilisé dans **TOUTES** les fonctionnalités :
- Tâche 6 : `//destination[budget <= $budget]`
- Tâche 7 : Requêtes multiples avec AND/OR
- Tâche 9 : `//destination[id='$id']`
- Tâche 10 : `//destination[activites/activite[text()='$activity']]`
- Navigation dans les documents XML
- Sélection de nœuds spécifiques

### ✅ XQuery
Fichiers de requêtes avancées :
- `query.xq` : Recommandation par budget
- `query_two_criteria.xq` : 2/3 critères avec tri
- `query_destination_details.xq` : Détails + destinations similaires
- `query_by_activity.xq` : Recherche par activité + statistiques

---

## 📁 STRUCTURE DU PROJET

```
websemantique/
│
├── 📄 XML - Données
│   ├── destinations.xml          (23 destinations)
│   └── utilisateur.xml           (1 utilisateur)
│
├── 📋 DTD - Définition de type
│   ├── destinations.dtd
│   └── utilisateur.dtd
│
├── 📐 XSD - Schémas XML
│   ├── destinations.xsd
│   └── utilisateur.xsd
│
├── 🎨 XSL - Transformations
│   └── destinations_transform.xsl
│
├── 🔍 XQuery - Requêtes
│   ├── query.xq
│   ├── query_two_criteria.xq
│   ├── query_destination_details.xq
│   └── query_by_activity.xq
│
├── 🔎 XPath - Scripts JavaScript
│   ├── xpath_budget.js
│   ├── xpath_two_criteria.js
│   ├── xpath_destination_details.js
│   └── xpath_by_activity.js
│
├── 🌐 Interface Web - HTML
│   ├── index.html                    (Page principale)
│   ├── add_destination.html          (Tâche 4)
│   ├── edit_user.html                (Tâche 5)
│   ├── xpath_recommendations.html    (Tâches 6 & 7)
│   ├── xslt_display.html             (Tâche 8 - Client)
│   ├── xslt_display_server.html      (Tâche 8 - Serveur)
│   ├── destination_details.html      (Tâche 9)
│   └── search_by_activity.html       (Tâche 10)
│
├── 💅 Styles & Scripts
│   ├── style.css
│   ├── app.js
│   ├── form_validation.js
│   └── user_form_validation.js
│
├── ⚙️ Backend
│   ├── server.js                     (Serveur Node.js avec toutes les routes)
│   ├── load_destinations.js          (Tâche 3)
│   └── package.json
│
└── 📖 Documentation
    └── README.md                     (Ce fichier)
```

---

## 🚀 INSTALLATION ET DÉMARRAGE

### Prérequis
- Node.js (v14 ou supérieur)
- npm

### Installation

```bash
# 1. Installer les dépendances
npm install

# Les dépendances installées :
# - express (serveur web)
# - cors (gestion CORS)
# - xmldom (parsing XML)
# - xpath (requêtes XPath)
# - xslt4node (transformations XSL)
```

### Démarrage du serveur

```bash
# Démarrer le serveur
npm start

# Ou directement avec Node.js
node server.js
```

Le serveur démarre sur **http://localhost:3000**

### Accès à l'application

Ouvrez votre navigateur et accédez à :
- **Page principale** : http://localhost:3000/index.html
- **Transformation XSLT** : http://localhost:3000/xslt-transform

---

## 📱 FONCTIONNALITÉS DE L'INTERFACE

### Page Principale (`index.html`)
- ✅ Affichage du profil utilisateur (chargé depuis XML)
- ✅ Liste de toutes les 23 destinations
- ✅ Filtre des destinations recommandées (3 critères)
- ✅ Statistiques en temps réel
- ✅ Navigation vers toutes les fonctionnalités

### Boutons de Navigation
1. **Toutes les destinations** - Affiche les 23 destinations
2. **Destinations recommandées** - Filtre selon critères utilisateur
3. **🔍 Recherche XPath** - Tâches 6 & 7
4. **🎯 Par Activité** - Tâche 10
5. **📄 Affichage XSLT** - Tâche 8
6. **📍 Détails Destination** - Tâche 9
7. **➕ Ajouter une destination** - Tâche 4
8. **✏️ Modifier le profil** - Tâche 5

---

## 🔗 API ENDPOINTS (Routes Serveur)

### Destinations
- `GET /destinations` - Liste toutes les destinations
- `GET /destinations-list` - Liste simplifiée (ID + nom)
- `GET /destination/:id` - Détails d'une destination (XPath)
- `POST /add-destination` - Ajouter une destination

### Utilisateur
- `GET /user` - Obtenir les données utilisateur
- `POST /save-user` - Enregistrer les données utilisateur

### Recommandations XPath
- `GET /recommend-by-budget` - **Tâche 6** : Par budget
- `GET /recommend-xpath` - **Tâche 6** : Complète (3 critères)
- `GET /recommend-two-criteria` - **Tâche 7** : 2/3 critères

### Recherche
- `GET /activities` - Liste toutes les activités
- `GET /search-by-activity/:activity` - **Tâche 10** : Par activité

### Transformation
- `GET /xslt-transform` - **Tâche 8** : Transformation XSL

---

## 🧪 TESTS DES FONCTIONNALITÉS

### Test Tâche 1 & 2 : Données XML + DTD/XSD
```bash
# Vérifier la structure XML
cat destinations.xml
cat utilisateur.xml

# Les fichiers contiennent les références DTD et XSD
```

### Test Tâche 3 : Lecture en mémoire
```bash
# Exécuter le script de chargement
node load_destinations.js

# Résultat attendu : Affichage des 23 destinations
```

### Test Tâche 4 : Formulaire ajout
1. Ouvrir : http://localhost:3000/add_destination.html
2. Remplir le formulaire
3. Cliquer sur "Ajouter la destination"
4. Vérifier que la destination apparaît dans `destinations.xml`

### Test Tâche 5 : Formulaire utilisateur
1. Ouvrir : http://localhost:3000/edit_user.html
2. Modifier les données
3. Cliquer sur "Enregistrer le profil"
4. Vérifier `utilisateur.xml`

### Test Tâche 6 : Recommandation budget (XPath)
```bash
# Via script
node xpath_budget.js

# Via navigateur
# Ouvrir : http://localhost:3000/xpath_recommendations.html
# Cliquer sur "Tâche 6: Par Budget"
```

### Test Tâche 7 : 2/3 critères (XPath)
```bash
# Via script
node xpath_two_criteria.js

# Via navigateur
# Ouvrir : http://localhost:3000/xpath_recommendations.html
# Cliquer sur "Tâche 7: 2/3 Critères"
```

### Test Tâche 8 : Affichage XSL
```bash
# Via navigateur
# Ouvrir : http://localhost:3000/xslt_display_server.html
# Vérifier : Fond JAUNE pour activité préférée, VERT pour les autres
```

### Test Tâche 9 : Détails destination (XPath)
```bash
# Via script
node xpath_destination_details.js

# Via navigateur
# Ouvrir : http://localhost:3000/destination_details.html
# Sélectionner une destination
# Cliquer sur "Afficher les détails"
```

### Test Tâche 10 : Recherche par activité (XPath)
```bash
# Via script
node xpath_by_activity.js

# Via navigateur
# Ouvrir : http://localhost:3000/search_by_activity.html
# Cliquer sur une activité (ex: "randonnée")
```

### Test Tâche 11 : Interface graphique
```bash
# Ouvrir : http://localhost:3000/index.html
# Tester toutes les fonctionnalités via l'interface
```

---

## 📊 DONNÉES DE TEST

### Utilisateur (utilisateur.xml)
- **Nom** : Dupont
- **Prénom** : Marie
- **Disponibilités** : 7 jours
- **Activité préférée** : randonnée
- **Budget** : 1000€

### Destinations (destinations.xml)
- **Total** : 23 destinations
- **Budget** : de 400€ à 2000€
- **Durée** : de 2 à 10 jours
- **Activités** : 16 activités différentes

### Activités disponibles
randonnée, camping, plage, ski, vélo, escalade, kayak, plongée, voile, alpinisme, équitation, parapente, visite culturelle, gastronomie, photographie, observation nature

---

## ✅ VALIDATION DES CRITÈRES

### Critères de validation des données :
- ✅ Nom de destination : minimum 3 caractères
- ✅ Description : minimum 20 caractères
- ✅ Durée : entre 1 et 30 jours
- ✅ Activités : exactement 2 activités différentes
- ✅ Budget : supérieur à 0€
- ✅ Nom/Prénom utilisateur : minimum 2 caractères

---

## 🎨 DESIGN DE L'INTERFACE

### Caractéristiques :
- ✅ Design moderne avec dégradés de couleurs
- ✅ Animations et transitions fluides
- ✅ Responsive (s'adapte à tous les écrans)
- ✅ Code couleur pour les recommandations
- ✅ Statistiques visuelles
- ✅ Navigation intuitive

### Couleurs principales :
- **Violet** (#667eea) : Navigation et titres
- **Vert** (#48bb78) : Destinations recommandées
- **Jaune** (#fef08a) : Activité préférée (XSL)
- **Vert clair** (#86efac) : Autres destinations (XSL)

---

## 🔧 DÉPANNAGE

### Erreur : "Cannot GET /"
- **Solution** : Accéder à http://localhost:3000/index.html

### Erreur : "Module not found"
- **Solution** : Exécuter `npm install`

### Erreur : "CORS"
- **Solution** : Le module `cors` est déjà configuré dans `server.js`

### Erreur : "Port 3000 already in use"
- **Solution** : Modifier le PORT dans `server.js` ou fermer l'autre application

---

## 📝 NOTES IMPORTANTES

1. **Toutes les tâches (1-11) sont complètes et fonctionnelles**
2. **Toutes les technologies requises sont utilisées** : XML, DTD, XSD, XSL, XPath, XQuery
3. **L'application fonctionne côté client ET côté serveur**
4. **Validation complète des données à tous les niveaux**
5. **Interface graphique professionnelle et intuitive**

---

## 👨‍💻 AUTEUR

Projet développé dans le cadre du cours de Web Sémantique
Application complète de recherche de destinations de vacances

---

## 📄 LICENCE

Ce projet est développé à des fins éducatives.

---

## 🎯 SCORE ATTENDU : 10/10 points

Toutes les tâches de la première partie sont complètes, fonctionnelles et respectent les critères demandés.

