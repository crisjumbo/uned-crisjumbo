package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.GTree;
import es.uned.lsi.eped.DataStructures.GTreeIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.Queue;
import es.uned.lsi.eped.DataStructures.QueueIF;

public class IndexTree implements IndexIF {

    protected GTreeIF<Node> index;
    
    public Seq_PSF retrieveIndex(String p) {
    	Seq_PSF emptyPSF;
    	emptyPSF = new Seq_PSF();
    	
    	// Comprobamos si el index es nulo o vacio
    	if (this.index == null || this.index.isEmpty()) {
    		return emptyPSF;
    	}
    	
    	GTreeIF<Node> currentGTree = this.index;
    	IteratorIF<GTreeIF<Node>> leafIterator;
    	
    	// Comparamos cada caracter de la palabra en cada nivel de arbol
    	for (int i = 0; i < p.length(); i++) {
    		char auxChar;
    		GTreeIF<Node> nextGTree;
    		IteratorIF<GTreeIF<Node>> childrenIterator;
    		
    		auxChar= p.charAt(i);
    		nextGTree = null;
    		childrenIterator = currentGTree.getChildren().iterator();
    		
    		// Buscamos el caracter dentro de los hijos del nodo actual
    		while (childrenIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node childRoot;
    			
    			childGTree = childrenIterator.getNext();
    			childRoot = childGTree.getRoot();
    			
    			if (childRoot.getNodeType() == Node.NodeType.INNER) {
    				if (((NodeInner) childRoot).getLetter()  == auxChar) {
    					nextGTree = childGTree;
    				}
    			}
    		}
    		
    		// Si la palabra no existe en el arbol, devolvemos una secuencia vacia
    		if (nextGTree == null) {
    			return emptyPSF;
    		}
    		
    		// Descendemos por el hijo que hace match con el caracter de la palabra
    		currentGTree = nextGTree;
    	}
    	
    	leafIterator = currentGTree.getChildren().iterator();
    	// Iteramos en el nodo correspondiente al ultimo caracter de la palabra
    	while (leafIterator.hasNext()) {
    		GTreeIF<Node> childGTree;
    		
    		childGTree = leafIterator.getNext();
    		
    		// Buscamos el nodo info con la secuencia
    		if (childGTree.getRoot().getNodeType() == Node.NodeType.INFO) {
    			return ((NodeInfo) childGTree.getRoot()).getSeqPSR();
    		}
    	}
    	
    	return emptyPSF;
    }
    
    public void insertIndex(String p, String doc_id, int freq) {
    	// Cuando index sea null, anadimos su nodo raiz
    	if (this.index == null) {
    		this.index = new GTree<Node>();
    		this.index.setRoot(new NodeRoot());
    	}
    	
    	GTreeIF<Node> currentGTree;
    	IteratorIF<GTreeIF<Node>> leafIterator;
    	NodeInfo infoNode;
    	
    	currentGTree = this.index;
    	
    	// Iteramos en cada caracter de la palabra
    	for (int i = 0; i < p.length(); i++) {
    		char auxChar;
    		int counter;
    		boolean found;
    		GTreeIF<Node> nextGTree;
    		IteratorIF<GTreeIF<Node>> childrenIterator;
    		
    		found = false;
    		counter = 1;
    		auxChar = p.charAt(i);
    		nextGTree = null;
    		childrenIterator = currentGTree.getChildren().iterator();
    		
    		// Iteramos en cada hijo del nodo padre con el caracter del nivel
    		while (childrenIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node root;
    			
    			childGTree = childrenIterator.getNext();
    			root = childGTree.getRoot();
    			
    			if (root.getNodeType() == Node.NodeType.INNER) {
    				char currentChar;
    				
    				currentChar = ((NodeInner) root).getLetter();
    				
    				// Si el caracter coincide con el nodo, saltamos al siguiente nivel de la rama
    				if (currentChar == auxChar) {
    					nextGTree = childGTree;
    					found = true;
    					break;
    				}
    				
    				// Si el caracter del nodo es mayor al del nivel, terminamos el bucle con la posicion dentro de los hijos
    				if (currentChar > auxChar) {
    					break;
    				}
    			}
    			
    			counter++;
    		}
    		
    		// Si no hay mas nodos en los hijos, creamos uno nuevo con el caracter actual
    		if (!found) {
    			GTreeIF<Node> newGTree;
    			
    			newGTree = new GTree<Node>();
    			newGTree.setRoot(new NodeInner(auxChar));
    			currentGTree.addChild(counter, newGTree);
    			nextGTree = newGTree;
    		}
    		
    		// Pasamos el iterador al siguiente nivel
    		currentGTree = nextGTree;
    		
    	}
    	
    	leafIterator = currentGTree.getChildren().iterator();
    	infoNode = null;
    	
    	// Iteramos los hijos de la ultima hoja de la rama del arbol para insertar el nodo info
    	while (leafIterator.hasNext()) {
    		Node root;
    		
    		root = leafIterator.getNext().getRoot();
    		
    		if (root.getNodeType() == Node.NodeType.INFO) {
    			infoNode = (NodeInfo) root;
    		}
    	}
    	
    	// Si el nodo info ya existia, anadimos un nuevo par en su sequencia PSR
    	if (infoNode != null) {
    		infoNode.getSeqPSR().add(new Pair_S_F(doc_id, freq));
    	// Si el nodo info no existia, se anade uno nuevo
    	} else {
    		NodeInfo newInfoNode;
    		GTreeIF<Node> infoGTree;
    		
    		newInfoNode = new NodeInfo(new Pair_S_F(doc_id, freq));
    		infoGTree = new GTree<Node>();
    		infoGTree.setRoot(newInfoNode);
    		currentGTree.addChild(1, infoGTree);
    	}
    	
    }
    
    private void collectWords(GTreeIF<Node> currentGTree, String currentWord, QueueIF<Pair_W_SeqPSF> wordPairs ) {
    	IteratorIF<GTreeIF<Node>> childrenIterator;
    	
    	childrenIterator = currentGTree.getChildren().iterator();
    	
    	// Iteramos en los nodos hijos del nodo padre
    	while(childrenIterator.hasNext()) {
    		GTreeIF<Node> childGTree;
    		Node root;
    		
    		childGTree = childrenIterator.getNext();
    		root = childGTree.getRoot();
    		
    		// Si hay un nodo info, lo metemos en cola
    		if (root.getNodeType() == Node.NodeType.INFO) {
    			wordPairs.enqueue(new Pair_W_SeqPSF(currentWord, ((NodeInfo) root).getSeqPSR()));
    		// Si no hay nodo y es inner, buscamos dentro de sus hijos de manera recursiva
    		} else if (root.getNodeType() == Node.NodeType.INNER) {
    			char auxChar;
    			
    			auxChar = ((NodeInner) root).getLetter();
    			collectWords(childGTree, currentWord + auxChar, wordPairs);
    		}
    	}
    }
    
    public IteratorIF<Pair_W_SeqPSF> prefixIterator(String prefix) {
    	// Si el indice es nulo o vacio, devolvemos null
    	if (this.index == null || this.index.isEmpty()) {
    		return null;
    	}
    	
    	GTreeIF<Node> currentGTree;
    	QueueIF<Pair_W_SeqPSF> wordPairs;
    	
    	currentGTree = this.index;
    	
    	// Iteramos en cada caracter de la palabra que equivale al nivel del arbol
    	for (int i = 0; i < prefix.length(); i++) {
    		char auxChar;
    		GTreeIF<Node> nextGTree;
    		IteratorIF<GTreeIF<Node>> childrenIterator;
    		
    		auxChar = prefix.charAt(i);
    		nextGTree = null;
    		childrenIterator = currentGTree.getChildren().iterator();
    		
    		//Iteramos en cada hijo del nodo actual
    		while (childrenIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node root;
    			
    			childGTree = childrenIterator.getNext();
    			root = childGTree.getRoot();
    			
    			// Si el caracter coincide, descendemos un nivel mas en la rama del arbol
    			if (root.getNodeType() == Node.NodeType.INNER && ((NodeInner) root).getLetter() == auxChar) {
    				nextGTree = childGTree;
    			}
    		}
    		
    		// Si el prefijo no existe en el arbol devolvemos nulo
    		if (nextGTree == null) {
    			return null;
    		}
    		
    		currentGTree = nextGTree;
    	}
    	
    	wordPairs = new Queue<Pair_W_SeqPSF>();
    	// Una vez en el ultimo nodo correspondiente al prefijo, de manera recursiva almacenamos los pares de cada hijo posible
    	collectWords(currentGTree, prefix, wordPairs);
    	return wordPairs.iterator();
    }
}
