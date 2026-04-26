package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.GTree;
import es.uned.lsi.eped.DataStructures.GTreeIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.Queue;
import es.uned.lsi.eped.DataStructures.QueueIF;

public class IndexTree implements IndexIF {

    protected GTreeIF<Node> index;
    
    public Seq_PSF retrieveIndex(String p) {
		if (this.index == null || this.index.isEmpty()) {
        return null;
    }

    GTreeIF<Node> currentNode = this.index;

    // 1. Navigate down the tree following the characters in String p
    for (int i = 0; i < p.length(); i++) {
        char targetChar = p.charAt(i);
        GTreeIF<Node> nextNode = null;

        // Search the children of the current node for the matching INNER node
        IteratorIF<GTreeIF<Node>> childrenIt = currentNode.getChildren().iterator();
        while (childrenIt.hasNext()) {
            GTreeIF<Node> child = childrenIt.getNext();
            Node root = child.getRoot();

            if (root.getNodeType() == Node.NodeType.INNER) {
                if (((NodeInner) root).getLetter() == targetChar) {
                    nextNode = child;
                    break;
                }
            }
        }

        // If we didn't find the character branch, the word isn't in our index
        if (nextNode == null) {
            return null;
        }
        currentNode = nextNode;
    }

    // 2. We reached the last character node. Now look for the INFO child.
    // In a Trie, the word data is stored as an INFO child of the last character's node.
    IteratorIF<GTreeIF<Node>> finalChildrenIt = currentNode.getChildren().iterator();
    while (finalChildrenIt.hasNext()) {
        GTreeIF<Node> child = finalChildrenIt.getNext();
        if (child.getRoot().getNodeType() == Node.NodeType.INFO) {
            return ((NodeInfo) child.getRoot()).getSeqPSR();
        }
    }

    return null; // Word found as a prefix, but no specific INFO node exists for it




    	// if(this.index.isEmpty()) {
    	// 	return null;
    	// }
    	
    	// int counter;
    	// QueueIF<NodeInner> auxQ;
		// IteratorIF<Node> treeIterator;
    	// Node cNode;
    	
    	// auxQ = new Queue<NodeInner>();
    	// counter = 0;
		// treeIterator = this.index.iterator(GTreeIF.IteratorModes.PREORDER);

    	// while (treeIterator.hasNext()) {
    	// 	cNode = treeIterator.getNext();
    		
    	// 	if(cNode.getNodeType() == Node.NodeType.INNER) {
    	// 		if (((NodeInner) cNode).getLetter() == p.charAt(counter)) {
    	// 			counter++;
    	// 		}
    			
    	// 		auxQ.enqueue((NodeInner)cNode);
    	// 	} else if (cNode.getNodeType() == Node.NodeType.INFO) {
    	// 		if (counter == p.length() & counter == auxQ.size()) {
    	// 			return ((NodeInfo) cNode).getSeqPSR();
    	// 		}
    	// 		counter = 0;
    	// 		auxQ.clear();
    	// 	} else if (cNode.getNodeType() == Node.NodeType.ROOT){
    	// 		counter = 0;
    	// 		auxQ.clear();
    	// 	}
    	// }
    	// return null;
    	
    }
    
    // Recorrer las lista de arboles, que coincidan las raices con cada palabra e insertar en children 1 el par
    public void insertIndex(String p, String doc_id, int freq) {
		// 1. Initialize the root if it doesn't exist
    if (this.index == null) {
        this.index = new GTree<Node>();
        this.index.setRoot(new NodeRoot());
    }

    GTreeIF<Node> currentNode = this.index;

    // 2. Traverse the tree character by character
    for (int i = 0; i < p.length(); i++) {
        char targetChar = p.charAt(i);
        GTreeIF<Node> nextNode = null;

        // Search among children for the current character
        IteratorIF<GTreeIF<Node>> childrenIt = currentNode.getChildren().iterator();
        int childPos = 1;
        while (childrenIt.hasNext()) {
            GTreeIF<Node> child = childrenIt.getNext();
            Node root = child.getRoot();
            
            if (root.getNodeType() == Node.NodeType.INNER) {
                if (((NodeInner) root).getLetter() == targetChar) {
                    nextNode = child;
                    break;
                }
            }
            childPos++;
        }

        // 3. If character not found, create the path
        if (nextNode == null) {
            GTreeIF<Node> newNode = new GTree<Node>();
            newNode.setRoot(new NodeInner(targetChar));
            // Add to the end of the children list
            currentNode.addChild(currentNode.getNumChildren() + 1, newNode);
            nextNode = newNode;
        }
        
        currentNode = nextNode;
    }

	// 2. SMART INSERTION: Check for existing INFO node
    IteratorIF<GTreeIF<Node>> finalChildren = currentNode.getChildren().iterator();
    NodeInfo existingInfo = null;
    
    while (finalChildren.hasNext()) {
        Node root = finalChildren.getNext().getRoot();
        if (root instanceof NodeInfo) {
            existingInfo = (NodeInfo) root;
            break;
        }
    }

    if (existingInfo != null) {
        // Word exists! Update the sequence with the new document/frequency
        existingInfo.getSeqPSR().add(new Pair_S_F(doc_id, freq));
    } else {
        // New word! Create the INFO node
        NodeInfo nodeInfo = new NodeInfo(new Pair_S_F(doc_id, freq));
        GTreeIF<Node> infoGTree = new GTree<Node>();
        infoGTree.setRoot(nodeInfo);
        currentNode.addChild(1, infoGTree); // Keep INFO nodes at position 1 for faster lookup
    }







    	// NodeInfo nodeInfo;
    	// GTreeIF<Node> infoGTree;
    	// IteratorIF<GTreeIF<Node>> treeIterator;
    	// int counter;
    	
    	// infoGTree = new GTree<Node>();
    	// nodeInfo = new NodeInfo(new Pair_S_F(doc_id, freq));
    	// infoGTree.setRoot(nodeInfo);
    	
    	// if (this.index == null ) {
    	// 	GTreeIF<Node> tmpGTree;
		// 	GTreeIF<Node> innerGTree;
    		
    	// 	this.index = new GTree<Node>();
		// 	innerGTree = new GTree<Node>();
    	// 	this.index.setRoot(new NodeRoot());
    	// 	counter = 1;
		// 	innerGTree.setRoot(new NodeInner(p.charAt(0)));
    	// 	this.index.addChild(1, innerGTree);
		// 	System.out.println("NULL : Index is null" + ((NodeInner) this.index.getChild(1).getRoot()).getLetter());
		// 	tmpGTree = new GTree<Node>();
    		
    	// 	while (counter < p.length()) {
    	// 		char auxChar = p.charAt(counter);
    			
		// 		System.out.println("NULL : Inserting character: " + auxChar);
    	// 		tmpGTree.setRoot(new NodeInner(auxChar));
    	// 		innerGTree.addChild(1, tmpGTree);
    	// 		innerGTree = tmpGTree;
    	// 		counter++;

    	// 		if (counter == p.length()) {
		// 			innerGTree.addChild(1, infoGTree);
		// 			System.out.println("NULL : Inserting info node" + innerGTree.getChild(1).getRoot().getNodeType());
    	// 			break;
    	// 		}
    	// 	}
    	// } else if (!this.index.getChildren().isEmpty()) {
        // 	treeIterator = this.index.getChildren().iterator();
        // 	counter = 0;
        	
		// 	System.out.println("NOT NULL : Index is not null");
        // 	while(treeIterator.hasNext()) {
        // 		GTreeIF<Node> auxGTree;
        		
        // 		// Change the iterator to the children that match character
        // 		auxGTree = treeIterator.getNext();
		// 		System.out.println("NOT NULL : Current node type: " + auxGTree.getRoot().getNodeType() + " Counter: " + counter);
        // 		if (auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
        //     		if (((NodeInner) auxGTree.getRoot()).getLetter() == p.charAt(counter)) {
        //     			treeIterator = auxGTree.getChildren().iterator();
        //     			counter++;
        //     			// If reached last character insert children info node
        //     			if (counter == p.length()) {
		// 					auxGTree.addChild(1, infoGTree);
		// 					System.out.println("NOT NULL : Inserting info node" + auxGTree.getChild(1).getRoot().getNodeType());
        //     				break;
        //     			}
        //     		// Add infoGTree if no character match
        //     		} else if(!treeIterator.hasNext()) {
        //     			// build infoGTree
        //     			GTreeIF<Node> tmpGTree;
		// 				GTreeIF<Node> innerGTree;
            			
		// 				innerGTree = new GTree<Node>();
		// 				innerGTree.setRoot(new NodeInner(p.charAt(counter)));
		// 				counter++;
		// 				if (counter == p.length()) {
		// 					auxGTree.addChild(auxGTree.getNumChildren() + 1, infoGTree);
		// 					System.out.println("NOT NULL : Added infoGTree to innerGTree" + innerGTree.getChild(1).getRoot().getNodeType());
		// 				} else {
		// 					auxGTree.addChild(auxGTree.getNumChildren() + 1, innerGTree);
		// 					System.out.println("NOT NULL : Added innerGTree to auxGTree" + auxGTree.getChild(auxGTree.getNumChildren()).getRoot().getNodeType());
		// 				}
		// 				tmpGTree = new GTree<Node>();

        //     			// New cycle to insert infoGTree
        //     			// Cycle to build infoGTree
        //     			while (counter < p.length()) {
        //     				char auxChar = p.charAt(counter);
            				
		// 					System.out.println("NOT NULL : Inserting character in infoGTree: " + auxChar);
        //     				tmpGTree.setRoot(new NodeInner(auxChar));
        //     				innerGTree.addChild(1, tmpGTree);
        //     				innerGTree = tmpGTree;
        //     				counter++;

        //     				if (counter == p.length()) {
		// 						System.out.println("NOT NULL : Adding infoGTree to innerGTree");
		// 						innerGTree.addChild(1, infoGTree);
        //     					break;
        //     				}
		// 				}
        //     		}
        // 		}
        // 	}
    	// }
    }
    
	/**
 * Recursive helper to explore the sub-tree and collect words.
 * @param node The current sub-tree root
 * @param currentWord The string reconstructed so far
 * @param results The queue to store found words
 */
private void collectWords(GTreeIF<Node> node, String currentWord, QueueIF<Pair_W_SeqPSF> results) {
    IteratorIF<GTreeIF<Node>> children = node.getChildren().iterator();

    while (children.hasNext()) {
        GTreeIF<Node> child = children.getNext();
        Node root = child.getRoot();

        if (root.getNodeType() == Node.NodeType.INFO) {
            // Found a word completion!
            results.enqueue(new Pair_W_SeqPSF(currentWord, ((NodeInfo) root).getSeqPSR()));
        } else if (root.getNodeType() == Node.NodeType.INNER) {
            // Keep going deeper, appending the new character
            char c = ((NodeInner) root).getLetter();
            collectWords(child, currentWord + c, results);
        }
    }
}

    public IteratorIF<Pair_W_SeqPSF> prefixIterator(String prefix) {
		if (this.index == null || this.index.isEmpty()) return null;

			GTreeIF<Node> currentNode = this.index;

			// Step 1: Reach the end of the prefix path
			for (int i = 0; i < prefix.length(); i++) {
				char target = prefix.charAt(i);
				GTreeIF<Node> nextNode = null;

				IteratorIF<GTreeIF<Node>> children = currentNode.getChildren().iterator();
				while (children.hasNext()) {
					GTreeIF<Node> child = children.getNext();
					Node root = child.getRoot();
					if (root.getNodeType() == Node.NodeType.INNER && ((NodeInner) root).getLetter() == target) {
						nextNode = child;
						break;
					}
				}

				if (nextNode == null) return null; // Prefix doesn't exist
				currentNode = nextNode;
			}

			// Step 2: Use recursion to find all words starting from currentNode
			QueueIF<Pair_W_SeqPSF> results = new Queue<Pair_W_SeqPSF>();
			collectWords(currentNode, prefix, results);

			return results.iterator();



    	// int counter;
    	// String auxStr;
    	// QueueIF<Pair_W_SeqPSF> pairWQueue;
    	// GTreeIF<Node> auxGTree;
    	// IteratorIF<GTreeIF<Node>> treeIterator;
    	// IteratorIF<Node> auxIterator;
    	
    	// counter = 0;
    	// pairWQueue = new Queue<Pair_W_SeqPSF>();
    	// treeIterator = this.index.getChildren().iterator();
 
    	// // Iterate till you reach last prefix character match node
    	// while(treeIterator.hasNext()) {
    	// 	auxGTree = treeIterator.getNext();
    		
    		
    	// 	if (((NodeInner) auxGTree.getRoot()).getLetter() == prefix.charAt(counter) & auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
    	// 		treeIterator = auxGTree.getChildren().iterator();
    	// 		counter++;
    			
    	// 		if (counter == prefix.length()) {
    	// 			auxIterator = auxGTree.iterator(GTreeIF.IteratorModes.PREORDER);
    	// 			auxStr = prefix;
    				
    	// 			while (auxIterator.hasNext()) {
    	// 				Node cNode;
    	// 				Pair_W_SeqPSF pairW;
    					
    	// 				cNode = auxIterator.getNext();
    	// 				if (cNode.getNodeType() == Node.NodeType.INNER) {
    	// 					auxStr = auxStr + ((NodeInner) cNode).getLetter();
    	// 				} else if (cNode.getNodeType() == Node.NodeType.INFO) {
    	// 					pairW = new Pair_W_SeqPSF(auxStr, ((NodeInfo) cNode).getSeqPSR());
    	// 					pairWQueue.enqueue(pairW);
    	// 				}
    					
    	// 			}
    	// 		}
    	// 		return pairWQueue.iterator();
    	// 	} else if (!treeIterator.hasNext() & auxGTree.getRoot().getNodeType() == Node.NodeType.INNER) {
    	// 		return null;
    	// 	}
    	// }
    	
    	// return null;
    }
}
