# Reponse aux question

## Question 1 :
* Affichage de pointeur au lieu de valeur (ligne `57/58`)
* Mauvaise logique de transaction (on retire l'argent avant de verifier si il est là)

## Question 2 :
### Code 1 :
```cpp
void foo(Creature c) {
    cout << "foo" << endl;
}

int main(int argc, char const *argv[])
{
    Creature ogre;
    Creature shrek = ogre;
    cout << "before foo" << endl;
    foo(shrek);
    cout << "after foo" << endl;
    return 0;
}
```
#### Affichage prévu :
1. duplication
1. before
1. ducplication
1. foo
1. destruction
1. after
1. destruction
1. destruction

#### Affichage réel :
```
>>> A creature has been duplicated
>>> before foo
>>> A creature has been duplicated
>>> foo
>>> A Creature has been destroyed
>>> after foo
>>> A Creature has been destroyed
>>> A Creature has been destroyed
```

### Code 2 :
```cpp
void foo(Creature &c) {
 cout << "foo" << endl;
 Creature a = c;
}

int main(int argc, char const *argv[])
{
 Creature ogre;
 cout << "before foo" << endl;
 foo(ogre);
 cout << "after foo" << endl;
 return 0;
}
```
#### Affichage prévu :
1. before
1. foo
1. duplication
1. destruction
1. after
1. destruction
#### Affichage réel :
```
>>> before foo
>>> foo
>>> A creature has been duplicated
>>> A Creature has been destroyed
>>> after foo
>>> A Creature has been destroyed
```

### Code 3 :
```cpp
void bar(Creature* c) {
 cout << "bar" << endl;
 delete c;
}

int main(int argc, char const *argv[])
{
 Creature ogre;
 Creature *shrek = new Creature(ogre);
 cout << "before bar" << endl;
 bar(shrek);
 cout << "after bar" << endl;
 return 0;
}
```
#### Affichage prévu :

1. duplication
1. before
1. bar
1. destruction
1. after
1. destruction

#### Affichage réel :
```
>>> A creature has been duplicated
>>> before bar
>>> bar
>>> A Creature has been destroyed
>>> after bar
>>> A Creature has been destroyed
```

### Code 4 :
```cpp
Creature foo(Creature &c) {
 cout << "foo" << endl;
 Creature local = c;
 return c;
}

int main(int argc, char const *argv[])
{
 Creature ogre;
 cout << "before foo" << endl;
 Creature shrek = foo(ogre);
 cout << "after foo" << endl;
 return 0;
}
```
#### Affichage prévu :
1. before
1. foo
1. duplication
1. duplication
1. destruction
1. after
1. destruction
1. destruction

#### Affichage réel :
```
>>> before foo
>>> foo
>>> A creature has been duplicated
>>> A creature has been duplicated
>>> A Creature has been destroyed
>>> after foo
>>> A Creature has been destroyed
>>> A Creature has been destroyed
```

### Passage par valeur 
Le programme crée une copie exacte (un clone indépendant) de la variable d'origine dans un nouvel emplacement mémoire.

La fonction travaille exclusivement sur cette copie. Les modifications apportées à l'intérieur de la fonction n'ont aucun impact sur la variable originale qui est restée dans le code appelant

L'objet copié existe uniquement le temps de l'exécution de la fonction. Dès que la fonction se termine, la copie est détruite (son destructeur est appelé).
#### Avantages :
* Pas de changement (securité).
* Simplicité : C'est litteralement une copie de l'original.

#### Inconvenients : 
* Plus de memoire utilisé (Performance Overhead d'après `Gemini`).
* Perte des modifications faite a l'interieur des fonctions.

### Passage par reference
La référence n'est pas une nouvelle variable indépendante. C'est un alias (un autre nom) donné à la variable originale en mémoire.

Tout ce qui est fait à l'intérieur de la fonction sur le paramètre de référence est fait directement sur l'objet d'origine dans le code appelant.

Aucun constructeur de copie n'est appelé lors du passage du paramètre.

#### Avantages :
* Meilleur performance, moins de place utilisée.
* Modification de l'objet par les fonction executé.

#### Inconvenients :
* On pert la securité du passage par valeur, toute action est sur l'objet en lui meme.
* Plus compliqué a lire, moins facile a comprendre au 1er coup d'oeil.