"""
Conversion d'un modele blender respectant ceraines regles 
vers Projet Univers.
"""

import Blender
import ogreexport
import re



	
# arbre de parente pour retrouver plus facilement les fils d'un objet
# c'est une fonction qui a chaque objet blender associe un ensemble d'objets blender


class Arbre:
	"""Arbre des relations entre objets blender, calcule les fils et les racines"""
	def __init__(self):
		self.fils = {}
		self.racines = []
		for objet in Blender.Object.Get():
			Ajouter(self, objet)
	

def Ajouter(arbre, objet):
	"""Ajoute l'objet dans l'arbre"""
	
	pere = objet.getParent()
	
	if pere == None:
		arbre.racines.append(objet)
	else:
		nomDuPere = pere.getName()
		if nomDuPere in arbre.fils.keys():
			arbre.fils[nomDuPere].append(objet)
		else:
			arbre.fils[nomDuPere] = [objet]

def Fils(arbre, objet):
	"""Recupere les fils d'un objet"""
	
	if objet.getName() in arbre.fils.keys():
	
		return arbre.fils[objet.getName()]

	else:
	
		return []

##############################################
# classes decrivants les differents composants
##############################################



# quelques constantes
TypeMoteur = 'MOTEUR'
TypeCoque = 'COQUE'
TypePoussee = 'POUSSEE'
TypeCentreGravite = 'CENTRE_GRAVITE'
TypeAttacheCoque = 'ATTACHE_COQUE'
TypeAttacheArme = 'ATTACHE_ARME'
TypeAttacheMoteur = 'ATTACHE_MOTEUR'
TypeAttacheTourelle = 'ATTACHE_TOURELLE'
TypeEtatMoteur = 'etat_moteur'

# une valeur mono-valuee optionelle
Optional = {}
	
	
def TypeComposant(objet):
	"""renvoie une chaine representant le type du composant"""
	return re.match("(?P<type>[a-zA-Z]*)(\.[0-9]*)?", objet.getName()).group('type')

		
class Composant:
	"""Classe abstraite des composants PU"""

	def __init__(self, objet):
		"""Constructeur, prend l'objet blender en parametre"""
		self.objet = objet
		
		
	def Erreurs(self):
		"""Renvoie les erreurs de validite du composant"""
		
		# si un attribut reste a None, alors il y a une erreur
		for attribut in self.__dict__:
			if self.__dict__[attribut] == None:
				print "sur l'objet " + self.objet.getName() + " il manque :" + attribut
	

###################################################
# Modele
###################################################	

		
class Modele(Composant):
	"""Un Mesh avec un niveau de details"""

	def __init__(self, objet):		
		"""initialisation"""
		
		Composant.__init__(self,objet)

		# attributs
		self.details = None

		# objets composants
		self.mesh = None
							

def ConversionModele(arbre, modele):
	"""Passage d'un objet blende modele a un objet de la classe Modele"""
	
	conversion = Modele(modele)
					
	for propriete in modele.getAllProperties():
	
		if propriete.getName() == 'details':

			conversion.details = propriete.getData()			

		else:

			print "erreur, la propriete " + propriete.getName() + " de " + modele.getName() + " n'est pas admise"
															
	conversion.mesh = modele
				
	return 


###################################################
# EtatMoteur
###################################################	

		
class EtatMoteur(Composant):
	"""Un moteur dans un certain etat de fraicheur"""
	
	def __init__(self, objet):		
		"""initialisation"""
		
		Composant.__init__(self,objet)
		
		# attributs
		self.degats = None
		self.masse = None
		self.poussee = None


		# objets composants
		self.vecteurPoussee = None
		self.centreGravite = None
		self.effet = None
		self.modeles = None
		self.attache = Optional

	def ConstruitObjetBlender(self, moteur):
		"""Construit les objets blender pour un etat de moteur
		   moteur est un objet blender representant un moteur
		"""
		
		if self.objet == None:
		
			nomEtatMoteur = NouveauNom(TypeEtatMoteur)
			etatMoteur = Blender.Object.New('Empty', nomEtatMoteur)
		
			moteur.makeParent([etatMoteur], noninverse = 1)
			
			if self.degats == None:
				degats = 0
			else:
				degats = self.degats
				
			etatMoteur.addProperty("degats", degats, "INT")
			
			
			etatMoteur.addProperty("masse", 0, "FLOAT")
			etatMoteur.addProperty("poussee", 0, "FLOAT")

			vecteurPoussee = Blender.Object.New('Empty',NouveauNom(TypeVecteurPoussee))
			centreGravite = Blender.Object.New('Empty',NouveauNom(TypeCentreGravite))
			effet = Blender.Object.New('Mesh', NouveauNom(TypeEffet))
			modele = 
			
		else:
			
			# l'objet est deja la, pas besoin de le construire
			return objet
		
		
		
		

def ConversionEtatMoteur(arbre,etatMoteur):
	"""Passage d'un objet blende etat moteur a un objet de la classe EtatMoteur"""
	
	etat = EtatMoteur(etatMoteur)
		
	for propriete in etatMoteur.getAllProperties():
		
		if propriete.getName() == 'degats':

			etat.degats = propriete.getData()
			
		elif propriete.getName() == 'masse':

			etat.masse = propriete.getData()			

		elif propriete.getName() == 'poussee':

			etat.pousse = propriete.getData()			
			
		else:
		
			print "erreur, la propriete " + propriete.getName() + " de " + etatMoteur.getName() + " n'est pas admise"
		
	fils = Fils(arbre,etatMoteur)
			
	for enfant in fils:
			
		if enfant.getType() == 'Empty' and TypeComposant(enfant) == TypeCentreGravite:
					
			etat.centreGravite = enfant
				
		elif enfant.getType() == 'Empty' and TypeComposant(enfant) == TypePoussee:
				
			etat.vecteurPoussee = enfant
				
		elif enfant.getType() == 'Mesh' and TypeComposant(enfant) == TypeEffetMoteur:
				
			etat.effetMoteur = enfant

		elif enfant.getType() == 'Mesh' and TypeComposant(enfant) == TypeAttacheCoque:
				
			etat.atache = enfant
					
		elif enfant.getType() == 'Mesh':
						
			modele = ConversionModele(arbre, enfant)		

			if etat.modeles == None:
					
				etat.modeles = [modele]
					
			else:
						
				etat.modeles.append(modele)

		else:
					
			print "erreur, le sous objet " + enfant.getName() + " de " + etatMoteur.getName() + " n'est pas admis"
									
	return etat
										
					
			
###################################################
# Moteur
###################################################	

	
class Moteur(Composant):
	"""Moteur dans PU"""

	def __init__(self, objet):		
		"""initialisation"""

		Composant.__init__(self,objet)
		
		# attributs
		self.nom = None
		self.constructeur = None

		# les differents etats de destruction du moteur
		self.etatsMoteur = None
		

def ConversionMoteur(arbre, moteur):
	""" Convertit un objet moteur.
	Precondition : moteur doit etre un objet Empty s'appelant MOTEUR.xxx
	"""
	
	conversion = Moteur(moteur)

	for propriete in moteur.getAllProperties():
		
		if propriete.getName() == 'nom':

			conversion.nom = propriete.getData()			

		elif propriete.getName() == 'constructeur':

			conversion.constructeur = propriete.getData()				

		elif propriete.getName() == 'resistance':

			conversion.resistance = propriete.getData()			

		else:

			print "erreur, la propriete " + propriete.getName() + " de " + moteur.getName() + " n'est pas admise"


	fils = Fils(arbre, moteur)
	
	for enfant in fils:

		if enfant.getType() == 'Empty':
		
			etatMoteur = ConversionEtatMoteur(arbre, enfant)
			
			if conversion.etatsMoteur == None:
				
				conversion.etatsMoteur = [etatMoteur]

			else:
	
				conversion.etatsMoteur.append(etatMoteur)

		else:
		
			print "erreur, le sous objet " + enfant.getName() + " de " + moteur.getName() + " n'est pas admis"

	return conversion


###################################################
# EtatCoque
###################################################	
			
class EtatCoque(Composant):
	"""Etat d'une Coque dans PU"""

	def __init__(self, objet):
		"""initialisation"""

		Composant.__init__(self,objet)
		
		# attributs
		self.masse = None
		self.degats = None
		
		# sous-objets
		self.modeles = None							
		self.centreGravite = None
		
		self.attacheMoteur = []
		self.attacheArme = []
		self.attacheTourelle = []
		
def ConversionEtatCoque(arbre, etatCoque):
	""" Convertit un objet etat coque"""

	conversion = EtatCoque(etatCoque)

	for propriete in etatCoque.getAllProperties():
		
		if propriete.getName() == 'masse':

			conversion.masse = propriete.getData()			

		elif propriete.getName() == 'degats':

			conversion.degats = propriete.getData()				

		else:

			print "erreur, la propriete " + propriete.getName() + " de " + etatCoque.getName() + " n'est pas admise"


	fils = Fils(arbre, etatCoque)
	
	for enfant in fils:

		if enfant.getType() == 'Empty' and TypeComposant(enfant) == TypeCentreGravite:
		
			conversion.centreGravite = enfant

		elif enfant.getType() == 'Empty' and TypeComposant(enfant) == TypeAttacheMoteur:

			conversion.attacheMoteur.append(enfant)

		elif enfant.getType() == 'Empty' and TypeComposant(enfant) == TypeAttacheArme:

			conversion.attacheArme.append(enfant)

		elif enfant.getType() == 'Empty' and TypeComposant(enfant) == TypeAttacheTourelle:

			conversion.attacheTourelle.append(enfant)

		elif enfant.getType() == 'Mesh':
		
			modele = ConversionModele(arbre,enfant)
			
			if conversion.modeles == None:
			
				conversion.modeles = [modele]
			
			else:
			
				conversion.modeles.append(modele)
				
		else:
		
			print "erreur, le sous objet " + enfant.getName() + " de " + etatCoque.getName() + " n'est pas admis"

	return conversion

	
							
##################################################################
# Coque
##################################################################			

class Coque(Composant):
	"""Coque dans PU"""
	
	def __init__(self, objet):
		"""initialisation"""
		
		Composant.__init__(self,objet)		

		self.resistance = None

		self.etats = None
		self.bouclier = Optional
																			

def ConversionCoque(arbre, coque):
	""" Convertit un objet coque"""

	conversion = Coque(coque)

	for propriete in coque.getAllProperties():
		
		if propriete.getName() == 'resistance':

			conversion.resistance = propriete.getData()			

		else:

			print "erreur, la propriete " + propriete.getName() + " de " + coque.getName() + " n'est pas admise"


	fils = Fils(arbre, coque)
	
	for enfant in fils:
		
		if enfant.getType() == 'Empty':
		
			etat = ConversionEtatCoque(arbre,enfant)
		
			if conversion.etats == None:
			
				conversion.etats = [etat]
			
			else:
			
				conversion.etats.append(etat)

	return conversion


		


###################################################
# Conversion d'un composant
###################################################	

					
	
					
def ConversionComposant(arbre, objet):
	"""Convertit un objet blender representant un composant en ses equivalent 
	PU"""
	
	# le nom de l'objet conditionnne le type du composant
	# le nom de l'objet doit etre d'une des deux formes suivantes : 
	# type
	# type.nombre
	type = re.match("(?P<type>[a-zA-Z]*)(\.[0-9]*)?", objet.getName()).group('type')

	# on appelle la bonne fonction de transformation
	if type == TypeMoteur:
		return ConversionMoteur(arbre, objet)

	else:
		return None


###################################################
# Main
###################################################	
	
	
# tests

#class Modele:
#	"""Encapsulation d'un modele blender"""
#	
#	def __init__(this, chemin):
#		"""On passe le chemin du modele"""
#	Blender.Load()
#	this.arbre = 	

#def ConversionModele(cheminModele, cheminDestination) :
#	"""Convertit un modele blender situe en cheminModele 
#	vers un modele PU situe en cheminDestination"""
	
	# 1. chargement du modele blender
	
	# 2. conversion des objets racines du modele
	
	# 3. fermeture du modele blender




#objets = Blender.Object.Get()
#print objets
#arbre = Arbre()
#for objet in objets:
#	Ajouter(arbre, objet)
#
#
#cube = Blender.Object.Get('Cube')
#print cube
#print Fils(arbre, cube)
#print arbre.racines

arbre = Arbre()
moteur = Blender.Object.Get('MOTEUR.001')
composantMoteur = ConversionComposant(arbre, moteur)
composantMoteur.Erreurs()
