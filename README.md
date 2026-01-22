# 📚 GUIDE D'EXPLICATION DÉTAILLÉ - PROJET WEB SÉMANTIQUE

## Guide complet pour expliquer chaque tâche au professeur

---

# PREMIÈRE PARTIE

---

## TÂCHE 1: Créer 20+ destinations et 1 utilisateur en XML (1 pt)

### 📄 Fichiers: `destinations.xml` et `utilisateur.xml`

### 🎯 Explication:
Nous avons créé des fichiers XML qui servent de base de données pour notre application.

**Structure XML Destinations:**
```xml
<destinations>
    <destination>
        <id>1</id>
        <nom>Alpes Françaises</nom>
        <description>...</description>
        <duree>7</duree>
        <activites>
            <activite>randonnée</activite>
            <activite>ski</activite>
        </activites>
        <budget>1200</budget>
    </destination>
    <!-- ... 22 autres destinations -->
</destinations>
```

**Points clés à expliquer:**
1. **23 destinations** créées (dépassant le minimum de 20)
2. Chaque destination contient: nom, description, durée (jours), 2 activités principales, budget
3. **1 utilisateur** avec: nom, prénom, disponibilités (jours), activité préférée, budget

---

## TÂCHE 2: Créer DTD/XSD (0.5 pt)

### 📄 Fichiers: `destinations.dtd`, `destinations.xsd`, `utilisateur.dtd`, `utilisateur.xsd`

### 🎯 Explication:

**DTD (Document Type Definition):**
```xml
<!ELEMENT destinations (destination+)>
<!ELEMENT destination (id, nom, description, duree, activites, budget)>
<!ELEMENT activites (activite, activite)>
```

**XSD (XML Schema Definition):**
```xml
<xs:element name="destinations">
    <xs:complexType>
        <xs:sequence>
            <xs:element name="destination" maxOccurs="unbounded">
                <xs:complexType>
                    <xs:sequence>
                        <xs:element name="id" type="xs:positiveInteger"/>
                        <xs:element name="budget" type="xs:decimal"/>
                        <xs:element name="activites">
                            <xs:complexType>
                                <xs:sequence>
                                    <xs:element name="activite" type="xs:string" minOccurs="2" maxOccurs="2"/>
                                </xs:sequence>
                            </xs:complexType>
                        </xs:element>
                    </xs:sequence>
                </xs:complexType>
            </xs:element>
        </xs:sequence>
    </xs:complexType>
</xs:element>
```

**Points clés:**
- **DTD**: Définit la structure simple du XML
- **XSD**: Plus puissant, avec types de données (positiveInteger, decimal, string)
- **Validation**: Les fichiers XML sont validés contre ces schémas pour assurer la cohérence

---

## TÂCHE 3: Lire destinations XML en mémoire (0.5 pt)

### 📄 Fichier: `load_destinations.js` et `server.js` (fonction `loadDestinationsFromXML()`)

### 🎯 Explication avec code:

**Code côté serveur (server.js):**
```javascript
function loadDestinationsFromXML() {
    // 1. Lire le fichier XML
    const xmlData = fs.readFileSync('destinations.xml', 'utf-8');
    
    // 2. Parser le XML avec DOMParser
    const parser = new DOMParser();
    const xmlDoc = parser.parseFromString(xmlData, 'text/xml');
    
    // 3. Extraire tous les éléments <destination>
    const destinationNodes = xmlDoc.getElementsByTagName('destination');
    
    // 4. Créer un tableau d'objets JavaScript
    destinationsInMemory = [];
    for (let i = 0; i < destinationNodes.length; i++) {
        const destNode = destinationNodes[i];
        
        // Extraire les activités
        const activitesNode = destNode.getElementsByTagName('activites')[0];
        const activiteNodes = activitesNode.getElementsByTagName('activite');
        const activites = [];
        for (let j = 0; j < activiteNodes.length; j++) {
            activites.push(activiteNodes[j].textContent);
        }
        
        // Créer l'objet destination
        destinationsInMemory.push({
            id: parseInt(destNode.getElementsByTagName('id')[0].textContent),
            nom: destNode.getElementsByTagName('nom')[0].textContent,
            description: destNode.getElementsByTagName('description')[0].textContent,
            duree: parseInt(destNode.getElementsByTagName('duree')[0].textContent),
            activites: activites,
            budget: parseFloat(destNode.getElementsByTagName('budget')[0].textContent)
        });
    }
    
    console.log(`✅ ${destinationsInMemory.length} destinations chargées en mémoire`);
}
```

**Comment ça fonctionne:**
1. **fs.readFileSync**: Lit le fichier XML du disque
2. **DOMParser**: Transforme le texte XML en objet DOM (Document Object Model)
3. **getElementsByTagName**: Récupère tous les éléments d'un type donné
4. **textContent**: Extrait le texte contenu dans un élément
5. Résultat: Tableau JavaScript `destinationsInMemory` contenant toutes les destinations

---

## TÂCHE 4: Formulaire pour ajouter destination avec validation (1 pt)

### 📄 Fichiers: `add_destination.html`, `form_validation.js`, `server.js`

### 🎯 Explication détaillée:

**1. Formulaire HTML (`add_destination.html`):**
```html
<form id="destinationForm">
    <input type="text" id="nom" name="nom" required>
    <textarea id="description" name="description" required></textarea>
    <input type="number" id="duree" name="duree" min="1" max="30" required>
    <select id="activite1" name="activite1" required>...</select>
    <select id="activite2" name="activite2" required>...</select>
    <input type="number" id="budget" name="budget" min="0" step="0.01" required>
</form>
```

**2. Validation côté client (`form_validation.js`):**
```javascript
function validateField(field) {
    const fieldName = field.name;
    let isValid = true;
    
    switch (fieldName) {
        case 'nom':
            if (!field.value.trim() || field.value.trim().length < 3) {
                isValid = false;
                errorMessage = 'Le nom doit contenir au moins 3 caractères';
            }
            break;
            
        case 'description':
            if (!field.value.trim() || field.value.trim().length < 20) {
                isValid = false;
                errorMessage = 'La description doit contenir au moins 20 caractères';
            }
            break;
            
        case 'duree':
            const duree = parseInt(field.value);
            if (duree < 1 || duree > 30) {
                isValid = false;
                errorMessage = 'La durée doit être entre 1 et 30 jours';
            }
            break;
            
        case 'budget':
            const budget = parseFloat(field.value);
            if (budget <= 0) {
                isValid = false;
                errorMessage = 'Le budget doit être supérieur à 0€';
            }
            break;
    }
    
    // Validation spéciale pour les activités
    function validateActivities() {
        const activite1 = document.getElementById('activite1').value;
        const activite2 = document.getElementById('activite2').value;
        
        if (activite1 === activite2) {
            isValid = false;
            errorMessage = 'Les deux activités doivent être différentes';
        }
    }
    
    return isValid;
}
```

**3. Envoi au serveur:**
```javascript
async function handleSubmit(event) {
    event.preventDefault();
    
    // Validation complète
    if (!validateForm()) {
        return;
    }
    
    // Préparer les données
    const formData = {
        nom: document.getElementById('nom').value.trim(),
        description: document.getElementById('description').value.trim(),
        duree: parseInt(document.getElementById('duree').value),
        activite1: document.getElementById('activite1').value,
        activite2: document.getElementById('activite2').value,
        budget: parseFloat(document.getElementById('budget').value)
    };
    
    // Envoyer au serveur via API REST
    const response = await fetch('http://localhost:3000/add-destination', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(formData)
    });
}
```

**4. Validation et sauvegarde côté serveur (`server.js`):**
```javascript
function validateDestination(data) {
    const errors = [];
    
    if (!data.nom || data.nom.trim().length < 3) {
        errors.push('Le nom doit contenir au moins 3 caractères');
    }
    
    if (!data.description || data.description.trim().length < 20) {
        errors.push('La description doit contenir au moins 20 caractères');
    }
    
    if (!data.duree || data.duree < 1 || data.duree > 30) {
        errors.push('La durée doit être entre 1 et 30 jours');
    }
    
    if (data.activite1 === data.activite2) {
        errors.push('Les deux activités doivent être différentes');
    }
    
    if (!data.budget || data.budget <= 0) {
        errors.push('Le budget doit être supérieur à 0€');
    }
    
    return errors; // Retourne tableau vide si tout est valide
}

function addDestinationToXML(newDestination) {
    // 1. Charger le XML actuel
    const xmlData = fs.readFileSync('destinations.xml', 'utf-8');
    const parser = new DOMParser();
    const xmlDoc = parser.parseFromString(xmlData, 'text/xml');
    
    // 2. Créer un nouvel élément <destination>
    const root = xmlDoc.getElementsByTagName('destinations')[0];
    const destinationElement = xmlDoc.createElement('destination');
    
    // 3. Ajouter tous les sous-éléments
    const idElement = xmlDoc.createElement('id');
    idElement.textContent = (Math.max(...destinationsInMemory.map(d => d.id)) + 1).toString();
    destinationElement.appendChild(idElement);
    
    const nomElement = xmlDoc.createElement('nom');
    nomElement.textContent = newDestination.nom;
    destinationElement.appendChild(nomElement);
    
    // ... (même chose pour description, duree, budget)
    
    // 4. Créer l'élément <activites>
    const activitesElement = xmlDoc.createElement('activites');
    const activite1Element = xmlDoc.createElement('activite');
    activite1Element.textContent = newDestination.activite1;
    activitesElement.appendChild(activite1Element);
    
    const activite2Element = xmlDoc.createElement('activite');
    activite2Element.textContent = newDestination.activite2;
    activitesElement.appendChild(activite2Element);
    
    destinationElement.appendChild(activitesElement);
    
    // 5. Ajouter au document et sauvegarder
    root.appendChild(destinationElement);
    
    const serializer = new XMLSerializer();
    const newXmlString = serializer.serializeToString(xmlDoc);
    fs.writeFileSync('destinations.xml', newXmlString, 'utf-8');
    
    // 6. Mettre à jour la liste en mémoire
    destinationsInMemory.push(newDestination);
}
```

**Points clés à expliquer:**
- **Double validation**: Client (rapide) + Serveur (sécurisé)
- **DOMParser**: Crée/modifie le XML
- **XMLSerializer**: Reconvertis l'objet DOM en texte XML
- **fs.writeFileSync**: Sauvegarde le fichier XML modifié

---

## TÂCHE 5: Formulaire utilisateur (1 pt)

### 📄 Fichiers: `edit_user.html`, `user_form_validation.js`, `server.js`

### 🎯 Explication:

**Code similaire à la tâche 4 mais pour les utilisateurs:**
```javascript
// Côté serveur
function saveUserToXML(userData) {
    // Créer le XML directement avec template string
    const xmlString = `<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE utilisateur SYSTEM "utilisateur.dtd">
<utilisateur>
    <nom>${userData.nom}</nom>
    <prenom>${userData.prenom}</prenom>
    <disponibilites>${userData.disponibilites}</disponibilites>
    <activite_preferee>${userData.activite_preferee}</activite_preferee>
    <budget>${userData.budget}</budget>
</utilisateur>`;
    
    // Sauvegarder
    fs.writeFileSync('utilisateur.xml', xmlString, 'utf-8');
}
```

**Points clés:**
- Remplace complètement le fichier `utilisateur.xml` (1 seul utilisateur)
- Validation des disponibilités (1-30 jours) et budget (>0)

---

## TÂCHE 6: Recommandation par budget avec XPath (1 pt)

### 📄 Fichiers: `xpath_recommendations.html`, `server.js` (route `/recommend-by-budget`)

### 🎯 Explication détaillée:

**Requête XPath utilisée:**
```xpath
//destination[budget <= 800]
```

**Code serveur:**
```javascript
app.get('/recommend-by-budget', (req, res) => {
    // 1. Charger l'utilisateur et extraire son budget avec XPath
    const userXml = fs.readFileSync('utilisateur.xml', 'utf-8');
    const userParser = new DOMParser();
    const userDoc = userParser.parseFromString(userXml, 'text/xml');
    
    // XPath pour extraire le budget de l'utilisateur
    const userBudget = parseFloat(xpath.select1('string(//budget)', userDoc));
    
    // 2. Charger les destinations
    const destXml = fs.readFileSync('destinations.xml', 'utf-8');
    const destParser = new DOMParser();
    const destDoc = destParser.parseFromString(destXml, 'text/xml');
    
    // 3. Requête XPath pour filtrer les destinations
    const xpathQuery = `//destination[budget <= ${userBudget}]`;
    
    // 4. Exécuter la requête XPath
    const destinationNodes = xpath.select(xpathQuery, destDoc);
    
    // 5. Convertir les nœuds en objets JavaScript
    const destinations = [];
    destinationNodes.forEach(node => {
        destinations.push({
            id: xpath.select1('string(id)', node),
            nom: xpath.select1('string(nom)', node),
            budget: parseFloat(xpath.select1('string(budget)', node))
            // ... autres propriétés
        });
    });
    
    res.json({
        success: true,
        xpath_query: xpathQuery,
        destinations: destinations
    });
});
```

**Comment expliquer XPath:**
- **`//destination`**: Sélectionne tous les éléments `<destination>` n'importe où dans le document
- **`[budget <= 800]`**: Filtre où le budget est <= 800
- **`xpath.select1()`**: Retourne un seul résultat (pour les valeurs uniques)
- **`xpath.select()`**: Retourne plusieurs résultats (pour les listes)

---

## TÂCHE 7: Recommandation avec 2/3 critères, triée (1 pt)

### 📄 Fichier: `server.js` (route `/recommend-two-criteria`)

### 🎯 Explication détaillée:

**Stratégie:**
1. Filtrer avec XPath pour chaque critère individuellement
2. Compter combien de critères sont satisfaits
3. Garder seulement ceux avec ≥2 critères
4. Trier par nombre de correspondances (DESC), puis budget (ASC)

**Code:**
```javascript
app.get('/recommend-two-criteria', (req, res) => {
    // Charger utilisateur
    const user = loadUserFromXML();
    
    // 3 requêtes XPath séparées
    const budgetQuery = `//destination[budget <= ${user.budget}]`;
    const durationQuery = `//destination[duree <= ${user.disponibilites}]`;
    const activityQuery = `//destination[activites/activite = '${user.activite_preferee}']`;
    
    // Exécuter les requêtes
    const budgetMatches = xpath.select(budgetQuery, destDoc);
    const durationMatches = xpath.select(durationQuery, destDoc);
    const activityMatches = xpath.select(activityQuery, destDoc);
    
    // Créer un Map pour compter les correspondances
    const matchCounts = new Map();
    
    // Compter pour chaque destination
    budgetMatches.forEach(node => {
        const nom = xpath.select1('string(nom)', node);
        matchCounts.set(nom, (matchCounts.get(nom) || 0) + 1);
    });
    durationMatches.forEach(node => {
        const nom = xpath.select1('string(nom)', node);
        matchCounts.set(nom, (matchCounts.get(nom) || 0) + 1);
    });
    activityMatches.forEach(node => {
        const nom = xpath.select1('string(nom)', node);
        matchCounts.set(nom, (matchCounts.get(nom) || 0) + 1);
    });
    
    // Filtrer: garder seulement ≥2 critères
    const destinations = [];
    matchCounts.forEach((count, nom) => {
        if (count >= 2) {
            // Trouver la destination complète
            const destNode = xpath.select1(`//destination[nom='${nom}']`, destDoc);
            destinations.push({
                nom: nom,
                matchCount: count,
                matchingCriteria: [], // Remplir selon les critères satisfaits
                budget: parseFloat(xpath.select1('string(budget)', destNode))
            });
        }
    });
    
    // Trier: d'abord par matchCount (DESC), puis par budget (ASC)
    destinations.sort((a, b) => {
        if (b.matchCount !== a.matchCount) {
            return b.matchCount - a.matchCount; // DESC
        }
        return a.budget - b.budget; // ASC
    });
    
    res.json({ destinations });
});
```

**Points clés:**
- **3 requêtes XPath distinctes** pour chaque critère
- **Comptage des correspondances** avec Map
- **Filtrage** pour garder ≥2 critères
- **Tri personnalisé** avec `sort()`

---

## TÂCHE 8: Affichage XSL avec fond jaune/vert (1 pt)

### 📄 Fichiers: `xslt_display.html`, `destinations_transform.xsl`

### 🎯 Explication détaillée:

**XSLT (eXtensible Stylesheet Language Transformations):**
Transforme le XML en HTML avec coloration conditionnelle.

**Feuille XSL (`destinations_transform.xsl`):**
```xml
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <!-- Paramètre: activité préférée de l'utilisateur -->
    <xsl:param name="userActivity">randonnée</xsl:param>
    
    <!-- Template principal -->
    <xsl:template match="/">
        <html>
            <!-- ... structure HTML ... -->
            <xsl:apply-templates select="destinations/destination"/>
        </html>
    </xsl:template>
    
    <!-- Template pour chaque destination -->
    <xsl:template match="destination">
        <div>
            <!-- Attribut conditionnel: classe CSS selon activité -->
            <xsl:attribute name="class">
                destination-card
                <xsl:choose>
                    <!-- Si cette destination contient l'activité préférée -->
                    <xsl:when test="activites/activite=$userActivity">
                        preferred  <!-- → Fond JAUNE -->
                    </xsl:when>
                    <xsl:otherwise>
                        other      <!-- → Fond VERT -->
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:attribute>
            
            <h3><xsl:value-of select="nom"/></h3>
            <p><xsl:value-of select="description"/></p>
            <!-- ... autres éléments ... -->
        </div>
    </xsl:template>
</xsl:stylesheet>
```

**Code JavaScript pour appliquer la transformation:**
```javascript
async function loadAndTransform() {
    // 1. Charger l'utilisateur pour obtenir l'activité préférée
    const userResponse = await fetch('utilisateur.xml');
    const userXmlText = await userResponse.text();
    const userParser = new DOMParser();
    const userXmlDoc = userParser.parseFromString(userXmlText, 'text/xml');
    const userActivity = userXmlDoc.querySelector('activite_preferee').textContent;
    
    // 2. Charger le XML des destinations
    const xmlResponse = await fetch('destinations.xml');
    const xmlText = await xmlResponse.text();
    const xmlDoc = xmlParser.parseFromString(xmlText, 'text/xml');
    
    // 3. Charger le fichier XSLT
    const xslResponse = await fetch('destinations_transform.xsl');
    const xslText = await xslResponse.text();
    const xslDoc = xslParser.parseFromString(xslText, 'text/xml');
    
    // 4. Créer le processeur XSLT
    const xsltProcessor = new XSLTProcessor();
    xsltProcessor.importStylesheet(xslDoc);
    
    // 5. Passer le paramètre (activité préférée)
    xsltProcessor.setParameter(null, 'userActivity', userActivity);
    
    // 6. Transformer le XML en HTML
    const resultDocument = xsltProcessor.transformToFragment(xmlDoc, document);
    
    // 7. Afficher le résultat
    document.getElementById('xslt-content').appendChild(resultDocument);
}
```

**Points clés:**
- **XSLT**: Langage de transformation XML → HTML
- **`xsl:param`**: Permet de passer des valeurs depuis JavaScript
- **`xsl:choose/when/otherwise`**: Logique conditionnelle
- **`xsl:value-of`**: Insère du texte
- **`XSLTProcessor`**: API du navigateur pour exécuter XSLT

---

## TÂCHE 9: Détails d'une destination avec XPath (1 pt)

### 📄 Fichiers: `destination_details.html`, `server.js` (route `/destination/:id`)

### 🎯 Explication:

**Requête XPath pour une destination spécifique:**
```xpath
//destination[id='3']
```

**Code serveur:**
```javascript
app.get('/destination/:id', (req, res) => {
    const destId = req.params.id;
    
    // Requête XPath pour trouver la destination par ID
    const xpathQuery = `//destination[id='${destId}']`;
    const destNode = xpath.select1(xpathQuery, destDoc);
    
    if (!destNode) {
        return res.json({ success: false, error: 'Destination non trouvée' });
    }
    
    // Extraire toutes les informations avec XPath
    const destination = {
        id: xpath.select1('string(id)', destNode),
        nom: xpath.select1('string(nom)', destNode),
        description: xpath.select1('string(description)', destNode),
        duree: parseInt(xpath.select1('string(duree)', destNode)),
        budget: parseFloat(xpath.select1('string(budget)', destNode)),
        activites: xpath.select('activites/activite', destNode).map(a => a.textContent)
    };
    
    res.json({
        success: true,
        xpath_query: xpathQuery,
        destination: destination
    });
});
```

**Points clés:**
- **`xpath.select1()`**: Pour un seul résultat
- **`xpath.select()`**: Pour les listes (activités)
- Extraction de chaque propriété individuellement

---

## TÂCHE 10: Liste destinations par activité avec XPath (1 pt)

### 📄 Fichiers: `search_by_activity.html`, `server.js` (route `/search-by-activity/:activity`)

### 🎯 Explication:

**Requête XPath:**
```xpath
//destination[activites/activite='randonnée']
```

**Code:**
```javascript
app.get('/search-by-activity/:activity', (req, res) => {
    const activity = req.params.activity;
    
    // Requête XPath pour trouver toutes les destinations avec cette activité
    const xpathQuery = `//destination[activites/activite='${activity}']`;
    const destinationNodes = xpath.select(xpathQuery, destDoc);
    
    const destinations = destinationNodes.map(node => ({
        nom: xpath.select1('string(nom)', node),
        budget: parseFloat(xpath.select1('string(budget)', node)),
        // ...
    }));
    
    // Tri par budget croissant
    destinations.sort((a, b) => a.budget - b.budget);
    
    res.json({
        success: true,
        xpath_query: xpathQuery,
        activity: activity,
        destinations: destinations
    });
});
```

**Points clés:**
- **`activites/activite`**: Chemin XPath vers les activités
- **`=`**: Comparaison exacte
- **Tri JavaScript** après extraction

---

## TÂCHE 11: Interface graphique (1 pt)

### 📄 Fichiers: `index.html`, `style.css`

### 🎯 Explication:

Interface moderne avec:
- **Navigation intuitive** entre toutes les fonctionnalités
- **Design responsive** (s'adapte aux écrans)
- **Couleurs et animations** pour une meilleure UX
- **Liens vers toutes les pages** des différentes tâches

**Structure:**
- Page d'accueil avec profil utilisateur
- Liste des destinations avec filtres
- Boutons pour accéder à chaque fonctionnalité

---

# DEUXIÈME PARTIE

---

## TÂCHE 1: Écrire RDF/XML pour le scénario (1 pt)

### 📄 Fichier: `recommendations.rdf`

### 🎯 Explication détaillée:

**RDF (Resource Description Framework):** Représente les données sous forme de triples (Sujet-Prédicat-Objet).

**Structure du fichier:**
```xml
<rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
         xmlns:vacation="http://www.example.org/vacation#">
    
    <!-- Classes -->
    <rdfs:Class rdf:about="http://www.example.org/vacation#User">
        <rdfs:label>User</rdfs:label>
    </rdfs:Class>
    
    <!-- Propriétés -->
    <rdf:Property rdf:about="http://www.example.org/vacation#hasBudget">
        <rdfs:domain rdf:resource="http://www.example.org/vacation#User"/>
        <rdfs:range rdf:resource="http://www.w3.org/2001/XMLSchema#decimal"/>
    </rdf:Property>
    
    <!-- Instances: Maria Popescu -->
    <vacation:User rdf:about="http://www.example.org/vacation#MariaPopescu">
        <rdfs:label>Maria Popescu</rdfs:label>
        <vacation:hasBudget rdf:datatype="http://www.w3.org/2001/XMLSchema#decimal">700</vacation:hasBudget>
        <vacation:hasAvailability rdf:datatype="http://www.w3.org/2001/XMLSchema#integer">5</vacation:hasAvailability>
        <vacation:prefersActivity rdf:resource="http://www.example.org/vacation#Randonnee"/>
    </vacation:User>
    
    <!-- Destination: Roumanie -->
    <vacation:Destination rdf:about="http://www.example.org/vacation#Roumanie">
        <rdfs:label>Roumanie</rdfs:label>
        <vacation:hasBudget rdf:datatype="http://www.w3.org/2001/XMLSchema#decimal">400</vacation:hasBudget>
        <vacation:hasDuration rdf:datatype="http://www.w3.org/2001/XMLSchema#integer">4</vacation:hasDuration>
        <vacation:hasActivity rdf:resource="http://www.example.org/vacation#Randonnee"/>
        <vacation:hasActivity rdf:resource="http://www.example.org/vacation#Tourisme"/>
        <vacation:isRecommendedFor rdf:resource="http://www.example.org/vacation#MariaPopescu"/>
    </vacation:Destination>
</rdf:RDF>
```

**Points clés:**
- **Triples RDF**: (MariaPopescu, hasBudget, 700)
- **URI**: Identifiants uniques (ex: `#MariaPopescu`)
- **Types de données**: decimal, integer
- **Relations**: `isRecommendedFor` lie destination à utilisateur

---

## TÂCHE 2: Visualiser RDF avec D3.js (1 pt)

### 📄 Fichier: `rdf_viewer.html`

### 🎯 Explication détaillée:

**1. Chargement et parsing du RDF:**
```javascript
async function loadDefaultRDF() {
    // 1. Charger le fichier RDF
    const response = await fetch('recommendations.rdf');
    const text = await response.text();
    
    // 2. Parser avec rdflib (API RDF équivalente à Jena)
    store = $rdf.graph(); // Créer un graphe vide
    const baseURI = 'http://www.example.org/vacation#';
    
    $rdf.parse(text, store, baseURI, 'application/rdf+xml');
    
    // 3. Extraire tous les triples
    currentTriples = store.statements;
    
    // 4. Visualiser
    visualizeGraph();
}
```

**2. Transformation en données pour D3.js:**
```javascript
function visualizeGraph() {
    const nodes = new Map();
    const links = [];
    
    // Pour chaque triple RDF
    currentTriples.forEach(triple => {
        const subject = triple.subject.value;  // Sujet
        const predicate = triple.predicate.value;  // Prédicat
        const object = triple.object.value;  // Objet
        
        // Ajouter les nœuds (sujet et objet)
        if (!nodes.has(subject)) {
            nodes.set(subject, {
                id: subject,
                label: getLabel(subject),
                type: getNodeType(subject) // 'user', 'destination', 'activity'
            });
        }
        
        if (!nodes.has(object)) {
            nodes.set(object, {
                id: object,
                label: getLabel(object),
                type: getNodeType(object)
            });
        }
        
        // Ajouter le lien (relation)
        links.push({
            source: subject,
            target: object,
            label: getLabel(predicate)
        });
    });
    
    // Créer la structure pour D3.js
    const graphData = {
        nodes: Array.from(nodes.values()),
        links: links
    };
    
    drawGraph(graphData);
}
```

**3. Visualisation avec D3.js:**
```javascript
function drawGraph(data) {
    const svg = d3.select('#graph')
        .append('svg')
        .attr('width', width)
        .attr('height', height);
    
    // Simulation physique (forces)
    const simulation = d3.forceSimulation(data.nodes)
        .force('link', d3.forceLink(data.links).id(d => d.id).distance(200))
        .force('charge', d3.forceManyBody().strength(-500)) // Répulsion
        .force('center', d3.forceCenter(width / 2, height / 2)); // Centrage
    
    // Dessiner les liens (lignes)
    const link = svg.append('g')
        .selectAll('line')
        .data(data.links)
        .enter().append('line')
        .attr('stroke', '#cbd5e0');
    
    // Dessiner les nœuds (cercles)
    const node = svg.append('g')
        .selectAll('circle')
        .data(data.nodes)
        .enter().append('circle')
        .attr('r', d => {
            if (d.type === 'user' || d.type === 'destination') return 25;
            return 18;
        })
        .attr('fill', d => {
            if (d.type === 'user') return '#667eea';
            if (d.type === 'destination') return '#48bb78';
            return '#ed8936';
        });
    
    // Dessiner les labels
    const label = svg.append('g')
        .selectAll('text')
        .data(data.nodes)
        .enter().append('text')
        .text(d => d.label);
    
    // Mise à jour de la position à chaque "tick" de la simulation
    simulation.on('tick', () => {
        link
            .attr('x1', d => d.source.x)
            .attr('y1', d => d.source.y)
            .attr('x2', d => d.target.x)
            .attr('y2', d => d.target.y);
        
        node
            .attr('cx', d => d.x)
            .attr('cy', d => d.y);
        
        label
            .attr('x', d => d.x)
            .attr('y', d => d.y);
    });
}
```

**Points clés:**
- **rdflib** = API RDF JavaScript (équivalent à Apache Jena en Java)
- **$rdf.parse()**: Parse RDF/XML en graphe de triples
- **D3.js force simulation**: Crée un layout automatique
- **Triple → Graphe**: Chaque triple devient une arête dans le graphe

---

## TÂCHE 3: Modifier/Ajouter destination dans RDF (1 pt)

### 📄 Fichier: `rdf_editor.html`

### 🎯 Explication:

**1. Charger le RDF existant:**
```javascript
async function loadExistingRDF() {
    const response = await fetch('recommendations.rdf');
    const text = await response.text();
    
    store = $rdf.graph();
    $rdf.parse(text, store, namespace, 'application/rdf+xml');
    
    displayDestinations();
}
```

**2. Modifier une destination existante:**
```javascript
// Quand l'utilisateur soumet le formulaire de modification
document.getElementById('modify-form').addEventListener('submit', function(e) {
    e.preventDefault();
    
    // 1. Supprimer tous les triples de cette destination
    store.removeMatches($rdf.sym(selectedDestination), null, null);
    
    // 2. Ajouter les nouveaux triples
    const nom = document.getElementById('modify-nom').value;
    const budget = document.getElementById('modify-budget').value;
    
    store.add(
        $rdf.sym(selectedDestination),           // Sujet
        $rdf.sym(namespace + 'hasBudget'),       // Prédicat
        $rdf.lit(budget, null, $rdf.sym('http://www.w3.org/2001/XMLSchema#decimal'))  // Objet
    );
    
    store.add(
        $rdf.sym(selectedDestination),
        $rdf.sym('http://www.w3.org/2000/01/rdf-schema#label'),
        $rdf.lit(nom)
    );
    
    // 3. Générer le RDF/XML modifié
    generateRDFOutput();
});
```

**3. Ajouter une nouvelle destination:**
```javascript
document.getElementById('add-form').addEventListener('submit', function(e) {
    e.preventDefault();
    
    const nom = document.getElementById('add-nom').value;
    const newUri = namespace + nom.replace(/\s+/g, '');
    
    // Créer tous les triples pour la nouvelle destination
    store.add($rdf.sym(newUri), 
              $rdf.sym('http://www.w3.org/1999/02/22-rdf-syntax-ns#type'), 
              $rdf.sym(namespace + 'Destination'));
    
    store.add($rdf.sym(newUri), 
              $rdf.sym('http://www.w3.org/2000/01/rdf-schema#label'), 
              $rdf.lit(nom));
    
    store.add($rdf.sym(newUri), 
              $rdf.sym(namespace + 'hasBudget'), 
              $rdf.lit(budget, null, $rdf.sym('http://www.w3.org/2001/XMLSchema#decimal')));
    
    // ... autres propriétés
    
    generateRDFOutput();
});
```

**4. Générer le RDF/XML:**
```javascript
function generateRDFOutput() {
    let rdfxml = '<?xml version="1.0" encoding="UTF-8"?>\n';
    rdfxml += '<rdf:RDF xmlns:rdf="..." xmlns:vacation="...">\n\n';
    
    // Grouper les triples par sujet
    const bySubject = {};
    store.statements.forEach(stmt => {
        const subject = stmt.subject.value;
        if (!bySubject[subject]) {
            bySubject[subject] = [];
        }
        bySubject[subject].push(stmt);
    });
    
    // Générer le XML
    Object.keys(bySubject).forEach(subject => {
        const statements = bySubject[subject];
        rdfxml += `    <vacation:Destination rdf:about="${subject}">\n`;
        
        statements.forEach(stmt => {
            const pred = stmt.predicate.value;
            const obj = stmt.object;
            
            if (obj.termType === 'Literal') {
                rdfxml += `        <vacation:hasBudget>${obj.value}</vacation:hasBudget>\n`;
            } else {
                rdfxml += `        <vacation:hasActivity rdf:resource="${obj.value}"/>\n`;
            }
        });
        
        rdfxml += `    </vacation:Destination>\n\n`;
    });
    
    rdfxml += '</rdf:RDF>';
    document.getElementById('rdf-output').textContent = rdfxml;
}
```

**Points clés:**
- **store.removeMatches()**: Supprime des triples
- **store.add()**: Ajoute des triples
- **$rdf.sym()**: Crée un URI
- **$rdf.lit()**: Crée un littéral (valeur)
- **Sérialisation manuelle**: Convertit le graphe en RDF/XML

---

## TÂCHE 4: Liste destinations RDF avec pages dédiées (1 pt)

### 📄 Fichiers: `rdf_destinations_list.html`, `rdf_destination_detail.html`

### 🎯 Explication:

**1. Liste des destinations:**
```javascript
function loadDestinationsFromRDF() {
    const response = await fetch('recommendations.rdf');
    const text = await response.text();
    
    $rdf.parse(text, store, namespace, 'application/rdf+xml');
    
    // Requête SPARQL-like: trouver toutes les destinations
    const destStatements = store.statementsMatching(
        null,  // N'importe quel sujet
        $rdf.sym('http://www.w3.org/1999/02/22-rdf-syntax-ns#type'),  // Prédicat: type
        $rdf.sym(namespace + 'Destination')  // Objet: Destination
    );
    
    // Extraire les propriétés de chaque destination
    destStatements.forEach(stmt => {
        const destUri = stmt.subject.value;
        
        const label = getPropertyValue(destUri, 'http://www.w3.org/2000/01/rdf-schema#label');
        const budget = getPropertyValue(destUri, namespace + 'hasBudget');
        const duration = getPropertyValue(destUri, namespace + 'hasDuration');
        const activities = getProperties(destUri, namespace + 'hasActivity');
        
        destinations.push({
            uri: destUri,
            label: label,
            budget: budget,
            duration: duration,
            activities: activities
        });
    });
    
    displayDestinations();
}

function getPropertyValue(subject, predicate) {
    const statements = store.statementsMatching(
        $rdf.sym(subject), 
        $rdf.sym(predicate), 
        null
    );
    return statements.length > 0 ? statements[0].object.value : null;
}
```

**2. Page de détails:**
```javascript
// Lors du clic sur une destination
function viewDestinationDetails(id) {
    window.location.href = `rdf_destination_detail.html?id=${id}`;
}

// Dans la page de détails
const urlParams = new URLSearchParams(window.location.search);
const destId = urlParams.get('id');
const destUri = namespace + destId;

// Extraire toutes les propriétés
const label = getPropertyValue(destUri, 'http://www.w3.org/2000/01/rdf-schema#label');
const budget = getPropertyValue(destUri, namespace + 'hasBudget');
const duration = getPropertyValue(destUri, namespace + 'hasDuration');
const activities = getProperties(destUri, namespace + 'hasActivity');

// Afficher dans l'interface
displayDestinationDetails({ label, budget, duration, activities });
```

**Points clés:**
- **statementsMatching()**: Requête de type SPARQL (triple pattern matching)
- **Passage de paramètres**: Via URL (`?id=Roumanie`)
- **Extraction systématique**: Une fonction pour chaque propriété

---

## TÂCHE 5: Interroger exigences (texte + graphique vert) (1.5 pt)

### 📄 Fichier: `rdf_query_destination.html`

### 🎯 Explication détaillée:

**1. Requête SPARQL (afficher):**
```javascript
function displaySPARQLQuery() {
    const sparqlQuery = `SELECT ?property ?value
WHERE {
    <${selectedDestination}> ?property ?value .
    FILTER (
        ?property = <${namespace}hasBudget> ||
        ?property = <${namespace}hasDuration> ||
        ?property = <${namespace}hasActivity>
    )
}`;
    
    document.getElementById('sparql-display').textContent = sparqlQuery;
}
```

**2. Exécution de la requête (simulée avec rdflib):**
```javascript
function executeQuery() {
    // Extraire les exigences (budget, durée, activités)
    const budget = getPropertyValue(selectedDestination, namespace + 'hasBudget');
    const duration = getPropertyValue(selectedDestination, namespace + 'hasDuration');
    const activities = getProperties(selectedDestination, namespace + 'hasActivity');
    
    // Afficher les résultats textuels
    const container = document.getElementById('text-results');
    container.innerHTML = `
        <div class="result-item">
            <div class="result-label">💰 Budget Requis</div>
            <div class="result-value">${budget}€</div>
        </div>
        <div class="result-item">
            <div class="result-label">⏱️ Durée Nécessaire</div>
            <div class="result-value">${duration} jours</div>
        </div>
        <div class="result-item">
            <div class="result-label">🎯 Activités Proposées</div>
            <div class="result-value">${activities.length} activité(s)</div>
        </div>
    `;
}
```

**3. Visualisation avec nœuds verts:**
```javascript
function displayColoredGraph() {
    // Récupérer tous les triples de cette destination
    const triples = store.statementsMatching(
        $rdf.sym(selectedDestination), 
        null,  // N'importe quel prédicat
        null   // N'importe quel objet
    );
    
    const nodes = new Map();
    const links = [];
    
    triples.forEach(triple => {
        const subject = triple.subject.value;
        const predicate = triple.predicate.value;
        const object = triple.object.value;
        
        // DÉTERMINER SI C'EST UNE EXIGENCE (à colorer en VERT)
        const isRequirement = 
            predicate.includes('hasBudget') || 
            predicate.includes('hasDuration') || 
            predicate.includes('hasActivity');
        
        if (!nodes.has(subject)) {
            nodes.set(subject, {
                id: subject,
                label: getLabel(subject),
                type: 'destination'
            });
        }
        
        if (!nodes.has(object)) {
            nodes.set(object, {
                id: object,
                label: getLabel(object),
                type: isRequirement ? 'requirement' : 'other'  // ← Type spécial
            });
        }
        
        links.push({
            source: subject,
            target: object,
            label: getLabel(predicate)
        });
    });
    
    drawColoredGraph({ nodes: Array.from(nodes.values()), links });
}

function drawColoredGraph(data) {
    const node = svg.append('g')
        .selectAll('circle')
        .data(data.nodes)
        .enter().append('circle')
        .attr('fill', d => {
            if (d.type === 'requirement') return '#48bb78';  // ← VERT
            if (d.type === 'destination') return '#667eea';
            return '#ed8936';
        })
        .attr('stroke', d => d.type === 'requirement' ? '#22543d' : '#2d3748')
        .attr('stroke-width', d => d.type === 'requirement' ? 3 : 2);  // ← Bordure épaisse
}
```

**Points clés:**
- **Filtrage par prédicat**: Identifier les exigences
- **Coloration conditionnelle**: Nœuds verts pour budget/durée/activités
- **Résultats textuels + graphiques**: Double présentation

---

## TÂCHE 6: Ontologie OWL avec restrictions (1 pt)

### 📄 Fichier: `vacation_ontology.owl`

### 🎯 Explication (conceptuelle):

**OWL (Web Ontology Language):** Langage pour créer des ontologies avec logique.

**Structure:**
```xml
<owl:Ontology rdf:about="http://www.example.org/vacation-ontology"/>

<!-- Classes -->
<owl:Class rdf:about="http://www.example.org/vacation-ontology#User"/>
<owl:Class rdf:about="http://www.example.org/vacation-ontology#Destination"/>

<!-- Propriétés -->
<owl:ObjectProperty rdf:about="http://www.example.org/vacation-ontology#prefersActivity">
    <rdfs:domain rdf:resource="#User"/>
    <rdfs:range rdf:resource="#Activity"/>
</owl:ObjectProperty>

<!-- Restrictions pour les règles de recommandation -->
<owl:Class rdf:about="#RecommendedDestination">
    <owl:equivalentClass>
        <owl:Class>
            <owl:intersectionOf>
                <rdf:Description>
                    <!-- Budget de destination <= Budget utilisateur -->
                </rdf:Description>
                <rdf:Description>
                    <!-- Durée <= Disponibilités -->
                </rdf:Description>
                <rdf:Description>
                    <!-- Activité principale correspond -->
                </rdf:Description>
            </owl:intersectionOf>
        </owl:Class>
    </owl:equivalentClass>
</owl:Class>
```

**Points clés:**
- **Classes OWL**: Plus expressives que RDF
- **Restrictions**: Définissent les règles logiques
- **Raisonnement**: Permet de déduire de nouvelles connaissances
- **Protégé/GraphDB**: Outils pour visualiser et raisonner

**À expliquer:**
1. Ouvrir dans Protégé
2. Voir les classes, propriétés, restrictions
3. Charger dans GraphDB
4. Visualiser le graphe de l'ontologie

---

## TÂCHE 7: 3 requêtes SPARQL (1.5 pt)

### 📄 Fichier: `sparql_owl.txt`

### 🎯 Explication des requêtes:

**Requête 1: Lister tous les utilisateurs**
```sparql
PREFIX vo: <http://www.example.org/vacation-ontology#>

SELECT ?user ?name ?budget ?availability ?preferredActivity
WHERE {
    ?user a vo:User .                    # ?user est de type User
    ?user vo:hasName ?name .             # Récupérer le nom
    ?user vo:hasBudget ?budget .         # Récupérer le budget
    ?user vo:hasAvailability ?availability .
    ?user vo:prefersActivity ?activity . # Lien vers l'activité
    ?activity vo:hasName ?preferredActivity .  # Nom de l'activité
}
ORDER BY ?budget
```

**Requête 2: Destinations recommandées pour Maria**
```sparql
SELECT ?destination ?destName ?destBudget ?destDuration ?principalActivity
WHERE {
    # L'utilisateur Maria Popescu
    ?user vo:hasName "Maria Popescu" .
    ?user vo:hasBudget ?userBudget .
    ?user vo:hasAvailability ?userAvailability .
    ?user vo:prefersActivity ?preferredActivity .
    
    # Destinations
    ?destination a vo:Destination .
    ?destination vo:hasName ?destName .
    ?destination vo:hasBudget ?destBudget .
    ?destination vo:hasDuration ?destDuration .
    ?destination vo:hasPrincipalActivity ?principalActivity .
    
    # Conditions (FILTER)
    FILTER (?destBudget <= ?userBudget)        # Budget OK
    FILTER (?destDuration <= ?userAvailability)  # Durée OK
    FILTER (?principalActivity = ?preferredActivity)  # Activité OK
}
```

**Requête 3: Statistiques sur destinations**
```sparql
SELECT ?destination ?destName ?budget ?duration 
       (GROUP_CONCAT(DISTINCT ?activityName; separator=", ") AS ?activities)
       (COUNT(DISTINCT ?activity) AS ?activityCount)
WHERE {
    ?destination a vo:Destination .
    ?destination vo:hasName ?destName .
    ?destination vo:hasBudget ?budget .
    ?destination vo:hasDuration ?duration .
    ?destination vo:hasActivity ?activity .
    ?activity vo:hasName ?activityName .
}
GROUP BY ?destination ?destName ?budget ?duration
ORDER BY ?budget
```

**Points clés à expliquer:**
- **PREFIX**: Définit les espaces de noms
- **SELECT**: Variables à retourner
- **WHERE**: Conditions (triple patterns)
- **FILTER**: Conditions supplémentaires
- **GROUP BY / COUNT**: Agrégations
- **ORDER BY**: Tri

**Comment tester:**
1. Ouvrir Protégé → Onglet SPARQL Query
2. Coller la requête
3. Exécuter
4. Capturer le résultat

---

## TÂCHE 8: Classification avec raisonneur (2 pt)

### 📄 Fichiers: `vacation_ontology.owl`, `vacation_ontology_asserted.owl`

### 🎯 Explication conceptuelle:

**Classification automatique:** Le raisonneur déduit automatiquement la classe d'un individu basé sur ses propriétés.

**Exemple à expliquer:**
1. **Créer un individu** dans Protégé:
   - Nom: "Jean Dupont"
   - Type: User
   - hasBudget: 600
   - hasAvailability: 5
   - prefersActivity: Randonnée

2. **Raisonneur analyse:**
   - Jean a un budget de 600€
   - Jean a 5 jours de disponibilité
   - Jean préfère la randonnée

3. **Comparaison avec destinations:**
   - Roumanie: budget 400€ (≤ 600) ✓, durée 4 jours (≤ 5) ✓, activité randonnée ✓
   - Le raisonneur **déduit**: Jean est éligible pour Roumanie

4. **Classification:**
   - L'ontologie peut avoir une classe `UserEligibleForRoumanie`
   - Le raisonneur **classe automatiquement** Jean dans cette classe

**Ontologie assertée vs inférée:**
- **Assertée** (`vacation_ontology_asserted.owl`): Données explicites que nous avons écrites
- **Inférée** (`vacation_ontology.owl` après raisonnement): Données déduites par le raisonneur

**Points clés:**
- **Raisonneur**: Pellet, HermiT, ELK (plugins Protégé)
- **Inférence**: Découverte automatique de nouvelles connaissances
- **Classification**: Attribution automatique de classes

**Comment démontrer:**
1. Ouvrir l'ontologie dans Protégé
2. Activer un raisonneur (Reasoner → Pellet)
3. Créer un individu avec certaines propriétés
4. Observer la classification automatique
5. Comparer l'ontologie avant/après raisonnement

---

## RÉSUMÉ POUR L'EXPLICATION

### Points techniques à souligner:

1. **XML/DOM**: Parsing et manipulation de documents XML
2. **XPath**: Requêtes pour naviguer et filtrer XML
3. **XSLT**: Transformation XML → HTML avec logique conditionnelle
4. **RDF**: Modèle de graphe avec triples (Sujet-Prédicat-Objet)
5. **SPARQL**: Langage de requête pour RDF (comme SQL pour bases de données)
6. **OWL**: Ontologies avec logique pour raisonnement
7. **rdflib**: API JavaScript pour manipuler RDF (équivalent Jena)

### Architecture du projet:

- **Frontend**: HTML/CSS/JavaScript (interfaces utilisateur)
- **Backend**: Node.js/Express (API REST)
- **Stockage**: Fichiers XML/RDF/OWL
- **Visualisation**: D3.js (graphes interactifs)

---

Bonne chance pour la présentation! 🎓
