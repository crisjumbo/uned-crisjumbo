package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.List;
import es.uned.lsi.eped.DataStructures.SequenceIF;

public class IndexSequence implements IndexIF {

    protected SequenceIF<Pair_W_SeqPSF> index;
    
    public IndexSequence() {
    	this.index = new List<Pair_W_SeqPSF>();
    }

    public Seq_PSF retrieveIndex(String p) {
    	IteratorIF<Pair_W_SeqPSF> iterator;
    	Pair_W_SeqPSF pair;
    	Seq_PSF foundPSF;
    	
    	iterator = this.index.iterator();
    	pair = new Pair_W_SeqPSF(p);
    	foundPSF = pair.getSeqPSR();
    	
    	// Iteramos la lista hasta encontrar la palabra
    	if (iterator != null) {
        	while(iterator.hasNext()) {
        		pair = iterator.getNext();
        		
        		if(pair.getWord().equals(p)) {
        			foundPSF = pair.getSeqPSR();
        			return foundPSF;
        		}
        	}
    	}
    	
    	return foundPSF;
    };
    

    public void insertIndex(String p, String doc_id, int freq) {
    	Seq_PSF seqPSF;
    	Pair_S_F pairSF;
    	IteratorIF<Pair_W_SeqPSF> listIterator;
    	int insertPosition;
    	boolean found;
    	
    	pairSF = new Pair_S_F(doc_id, freq);
    	seqPSF = new Seq_PSF();
    	seqPSF.add(pairSF);
    	insertPosition = 1;
    	found = false;
    	
    	if (this.index.isEmpty()) {
    		((List<Pair_W_SeqPSF>) this.index).insert(insertPosition, new Pair_W_SeqPSF(p, seqPSF));
    	} else {
    		listIterator = this.index.iterator();
    		// Iteramos la lista hasta encontrar la palabra o encontrar su posicion en la lista
    		while(listIterator.hasNext()) {
    			Pair_W_SeqPSF currentPair;
    			
    			currentPair = listIterator.getNext();
    			if (currentPair.getWord().equals(p)) {
    				currentPair.getSeqPSR().add(pairSF);
    				found = true;
    				break;
    			}
    			if (currentPair.getWord().compareTo(p) > 0) {
    				break;
    			}
    			insertPosition++;
    		}
    		
    		// Si el par no estaba en la lisa, se inserta en la posicion indicada
    		if (!found) {
    			((List<Pair_W_SeqPSF>) this.index).insert(insertPosition, new Pair_W_SeqPSF(p, seqPSF));
    		}
    	}
    }


    public IteratorIF<Pair_W_SeqPSF> prefixIterator(String prefix) {
    	// Creo una Lista vacia en la que insertar las palabras previas ordenadas
    	SequenceIF<Pair_W_SeqPSF> auxIndex;
    	IteratorIF<Pair_W_SeqPSF> iteratorMain;
    	int counter;
    	
    	auxIndex = new List<Pair_W_SeqPSF>();
    	iteratorMain = this.index.iterator();
		counter = 1;
    	
		// Iteramos toda la lista para almacenar las palabras con el prefijo
		if (iteratorMain != null) {
	    	while(iteratorMain.hasNext()) {
	    		Pair_W_SeqPSF currentWPair;
	    		
	    		currentWPair = iteratorMain.getNext(); 
	    		
	    		// Compruebo que la palabra de la secuencia tenga el prefix indicado
	    		if(currentWPair.getWord().startsWith(prefix)) {
	    			((List<Pair_W_SeqPSF>) auxIndex).insert(counter, currentWPair);
	    			counter++;
	    		}
	    	}
		}


    	return auxIndex.iterator();
    }
}
