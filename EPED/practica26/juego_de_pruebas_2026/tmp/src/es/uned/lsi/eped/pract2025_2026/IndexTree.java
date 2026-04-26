package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.GTree;
import es.uned.lsi.eped.DataStructures.GTreeIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.Queue;
import es.uned.lsi.eped.DataStructures.QueueIF;

public class IndexTree implements IndexIF {

    protected GTreeIF<Node> index;
    
    public Seq_PSF retrieveIndex(String p) {
    	if(this.index.isEmpty()) {
    		return null;
    	}
    	
    	int counter;
    	QueueIF<NodeInner> auxQ;
    	Node cNode;
    	
    	auxQ = new Queue<NodeInner>();
    	counter = 0;
    	while (this.index.iterator(GTreeIF.IteratorModes.PREORDER).hasNext()) {
    		cNode = this.index.iterator(GTreeIF.IteratorModes.PREORDER).getNext();
    		
    		if(cNode.getNodeType() == Node.NodeType.INNER) {
    			if (((NodeInner) cNode).getLetter() == p.charAt(counter)) {
    				counter++;
    			}
    			
    			auxQ.enqueue((NodeInner)cNode);
    		} else if (cNode.getNodeType() == Node.NodeType.INFO) {
    			if (counter == p.length() & counter == auxQ.size()) {
    				return ((NodeInfo) cNode).getSeqPSR();
    			}
    			counter = 0;
    			auxQ.clear();
    		} else if (cNode.getNodeType() == Node.NodeType.ROOT){
    			counter = 0;
    			auxQ.clear();
    		}
    	}
    	return null;
    	
    }
    
    // Recorrer las lista de arboles, que coincidan las raices con cada palabra e insertar en children 1 el par
    public void insertIndex(String p, String doc_id, int freq) {
    	NodeInfo nodeInfo;
    	GTreeIF<Node> infoGTree;
    	IteratorIF<GTreeIF<Node>> treeIterator;
    	int counter;
    	
    	infoGTree = new GTree<Node>();
    	nodeInfo = new NodeInfo(new Pair_S_F(doc_id, freq));
    	infoGTree.setRoot(nodeInfo);
    	
    	if (this.index == null ) {
    		GTreeIF<Node> tmpGTree;
    		
    		this.index = new GTree<Node>();
    		this.index.setRoot(new NodeRoot());
    		counter = 0;
    		this.index.addChild(1, infoGTree);
    		tmpGTree = new GTree<Node>();
    		
    		while (counter < p.length()) {
    			char auxChar = p.charAt(counter);
    			
    			tmpGTree.clear();
    			tmpGTree.setRoot(new NodeInner(auxChar));
    			infoGTree.addChild(1, tmpGTree);
    			infoGTree = infoGTree.getChild(1);
    			counter++;
    			if (counter == p.length()) {
    				infoGTree.setRoot(nodeInfo);
    				break;
    			}
    		}
    	} else if (!this.index.getChildren().isEmpty()) {
        	treeIterator = this.index.getChildren().iterator();
        	counter = 0;
        	
        	while(treeIterator.hasNext()) {
        		GTreeIF<Node> auxGTree;
        		
        		// Change the iterator to the children that match character
        		auxGTree = treeIterator.getNext();
        		if (auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
            		if (((NodeInner) auxGTree.getRoot()).getLetter() == p.charAt(counter)) {
            			treeIterator = auxGTree.getChildren().iterator();
            			counter++;
            			// If reached last character insert children info node
            			if (counter == p.length()) {
            				auxGTree.addChild(1, infoGTree);
            				break;
            			}
            		// Add infoGTree if no character match
            		} else if(!treeIterator.hasNext()) {
            			// build infoGTree
            			GTreeIF<Node> tmpGTree;
            			
            			tmpGTree = new GTree<Node>();
            			auxGTree.addChild(auxGTree.getNumChildren() + 1, infoGTree);
            			// New cycle to insert infoGTree
            			// Cycle to build infoGTree
            			while (counter < p.length()) {
            				char auxChar = p.charAt(counter);
            				
            				tmpGTree.setRoot(new NodeInner(auxChar));
            				infoGTree.addChild(1, tmpGTree);
            				tmpGTree.clear();
            				infoGTree = infoGTree.getChild(1);
            				counter++;
            				if (counter == p.length()) {
            					infoGTree.setRoot(nodeInfo);
            					break;
            				}
            			}
            		}
        		}
        	}
    	}
    }
    
    public IteratorIF<Pair_W_SeqPSF> prefixIterator(String prefix) {
    	int counter;
    	String auxStr;
    	QueueIF<Pair_W_SeqPSF> pairWQueue;
    	GTreeIF<Node> auxGTree;
    	IteratorIF<GTreeIF<Node>> treeIterator;
    	IteratorIF<Node> auxIterator;
    	
    	counter = 0;
    	pairWQueue = new Queue<Pair_W_SeqPSF>();
    	treeIterator = this.index.getChildren().iterator();
 
    	// Iterate till you reach last prefix character match node
    	while(treeIterator.hasNext()) {
    		auxGTree = treeIterator.getNext();
    		
    		
    		if (((NodeInner) auxGTree.getRoot()).getLetter() == prefix.charAt(counter) & auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
    			treeIterator = auxGTree.getChildren().iterator();
    			counter++;
    			
    			if (counter == prefix.length()) {
    				auxIterator = auxGTree.iterator(GTreeIF.IteratorModes.PREORDER);
    				auxStr = prefix;
    				
    				while (auxIterator.hasNext()) {
    					Node cNode;
    					Pair_W_SeqPSF pairW;
    					
    					cNode = auxIterator.getNext();
    					if (cNode.getNodeType() == Node.NodeType.INNER) {
    						auxStr = auxStr + ((NodeInner) cNode).getLetter();
    					} else if (cNode.getNodeType() == Node.NodeType.INFO) {
    						pairW = new Pair_W_SeqPSF(auxStr, ((NodeInfo) cNode).getSeqPSR());
    						pairWQueue.enqueue(pairW);
    					}
    					
    				}
    			}
    			return pairWQueue.iterator();
    		} else if (!treeIterator.hasNext() & auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
    			return null;
    		}
    	}
    	
    	return null;
    }
}
