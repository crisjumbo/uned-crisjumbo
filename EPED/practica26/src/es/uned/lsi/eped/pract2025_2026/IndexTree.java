package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.GTree;
import es.uned.lsi.eped.DataStructures.GTreeIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.Queue;
import es.uned.lsi.eped.DataStructures.QueueIF;

public class IndexTree implements IndexIF {

    protected GTreeIF<Node> index;
    
    public Seq_PSF retrieveIndex(String p) {
    	Seq_PSF seqPSF;
    	
    	seqPSF = new Seq_PSF();
    	// Comprobamos si el index es nulo o vacio
    	if (this.index == null || this.index.isEmpty()) {
    		return seqPSF;
    	}
    	
    	GTreeIF<Node> currentGTree = this.index;
    	IteratorIF<GTreeIF<Node>> leafIterator;
    	
    	// Buscamos cada caracter por cada nivel del arbol
    	for (int i = 0; i < p.length(); i++) {
    		char auxChar;
    		GTreeIF<Node> nextGTree;
    		IteratorIF<GTreeIF<Node>> childrenTreeIterator;
    		
    		auxChar= p.charAt(i);
    		nextGTree = null;
    		childrenTreeIterator = currentGTree.getChildren().iterator();
    		
    		// Buscamos el caracter dentro de los hijos del nodo actual
    		while (childrenTreeIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node childRoot;
    			
    			childGTree = childrenTreeIterator.getNext();
    			childRoot = childGTree.getRoot();
    			
    			if (childRoot.getNodeType() == Node.NodeType.INNER) {
    				if (((NodeInner) childRoot).getLetter()  == auxChar) {
    					nextGTree = childGTree;
    				}
    			}
    		}
    		
    		if (nextGTree == null) {
    			return seqPSF;
    		}
    		currentGTree = nextGTree;
    	}
    	
    	// Una vez en el penultimo nodo de la rama, buscamos el nodo hoja INFO
    	leafIterator = currentGTree.getChildren().iterator();
    	while (leafIterator.hasNext()) {
    		GTreeIF<Node> childGTree;
    		
    		childGTree = leafIterator.getNext();
    		
    		if (childGTree.getRoot().getNodeType() == Node.NodeType.INFO) {
    			return ((NodeInfo) childGTree.getRoot()).getSeqPSR();
    		}
    	}
    	
    	return seqPSF;
    }
    
    // Recorrer las lista de arboles, que coincidan las raices con cada palabra e insertar en children 1 el par
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
    		
    		// Iteramos en cada hijo del nodo padre
    		while (childrenIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node root;
    			
    			childGTree = childrenIterator.getNext();
    			root = childGTree.getRoot();
    			
    			// Si el caracter coincide con el nodo, saltamos al siguiente nivel de la rama
    			if (root.getNodeType() == Node.NodeType.INNER) {
    				char currentChar;
    				
    				currentChar = ((NodeInner) root).getLetter();
    				
    				if (currentChar == auxChar) {
    					nextGTree = childGTree;
    					found = true;
    					break;
    				}
    				
    				if (currentChar > auxChar) {
    					break;
    				}
    			}
    			
    			counter++;
    		}
    		
    		// Si no hay mas nodos, creamos uno nuevo con el caracter actual
    		if (!found) {
    			GTreeIF<Node> newGTree;
    			
    			newGTree = new GTree<Node>();
    			newGTree.setRoot(new NodeInner(auxChar));
    			currentGTree.addChild(counter, newGTree);
    			nextGTree = newGTree;
    		}
    		
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
    	
    	while(childrenIterator.hasNext()) {
    		GTreeIF<Node> childGTree;
    		Node root;
    		
    		childGTree = childrenIterator.getNext();
    		root = childGTree.getRoot();
    		
    		if (root.getNodeType() == Node.NodeType.INFO) {
    			wordPairs.enqueue(new Pair_W_SeqPSF(currentWord, ((NodeInfo) root).getSeqPSR()));
    		} else if (root.getNodeType() == Node.NodeType.INNER) {
    			char auxChar;
    			
    			auxChar = ((NodeInner) root).getLetter();
    			collectWords(childGTree, currentWord + auxChar, wordPairs);
    		}
    	}
    }
    
    public IteratorIF<Pair_W_SeqPSF> prefixIterator(String prefix) {
    	if (this.index == null || this.index.isEmpty()) {
    		return null;
    	}
    	
    	GTreeIF<Node> currentGTree;
    	QueueIF<Pair_W_SeqPSF> wordPairs;
    	
    	currentGTree = this.index;
    	
    	for (int i = 0; i < prefix.length(); i++) {
    		char auxChar;
    		GTreeIF<Node> nextGTree;
    		IteratorIF<GTreeIF<Node>> childrenIterator;
    		
    		auxChar = prefix.charAt(i);
    		nextGTree = null;
    		childrenIterator = currentGTree.getChildren().iterator();
    		while (childrenIterator.hasNext()) {
    			GTreeIF<Node> childGTree;
    			Node root;
    			
    			childGTree = childrenIterator.getNext();
    			root = childGTree.getRoot();
    			
    			if (root.getNodeType() == Node.NodeType.INNER && ((NodeInner) root).getLetter() == auxChar) {
    				nextGTree = childGTree;
    			}
    		}
    		
    		if (nextGTree == null) {
    			return null;
    		}
    		currentGTree = nextGTree;
    	}
    	
    	wordPairs = new Queue<Pair_W_SeqPSF>();
    	collectWords(currentGTree, prefix, wordPairs);
    	return wordPairs.iterator();
    }
}
