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
    	
    	iterator = index.iterator();
    	iterator.reset();
    	
    	while(iterator.hasNext()) {
    		Pair_W_SeqPSF pair;
    		pair = iterator.getNext();
    		
    		if(pair.getWord().equals(p)) {
    			return pair.getSeqPSR();
    		}
    	}
    	
    	return null;
    };
    

    public void insertIndex(String p, String doc_id, int freq) {
    	if (index.isEmpty()) {
    		// Si la secuencia de frecuencia de palabras esta vacia.
    		// Inserta la secuencia de frecuencia con la palabra
    		Seq_PSF seqPSF;
    		
    		seqPSF = new Seq_PSF();
    		seqPSF.add(new Pair_S_F(doc_id, freq));
    		((List<Pair_W_SeqPSF>) index).insert(1, new Pair_W_SeqPSF(p, seqPSF));
    	}else {
    		IteratorIF<Pair_W_SeqPSF> iteratorMain;
    		int counterMain;
    		
    		iteratorMain = this.index.iterator();
    		iteratorMain.reset();
    		counterMain = 0;
    		// Recorremos la secuencia de palabras para ver si el parametro "p" coincide con la secuencia
    		while(iteratorMain.hasNext()) {
    			Pair_W_SeqPSF currentWPair;
    			
    			counterMain++;
    			currentWPair = iteratorMain.getNext();
    			
    			// Si la palabra en secuencia es igual, "p" se anade despues de la palabra
    			if (currentWPair.getWord().equals(p) ) {
    				Seq_PSF seqPSF = currentWPair.getSeqPSR();
    				
    				seqPSF.add(new Pair_S_F(doc_id, freq));
    				((List<Pair_W_SeqPSF>) index).insert(counterMain + 1,new Pair_W_SeqPSF(p, seqPSF));
    			} else {
    				Seq_PSF seqPSF = currentWPair.getSeqPSR();
    				
    				// Si "p" es mayor a la palabra de secuencia se inserta como la siguiente palabra en secuencia
    				if (currentWPair.getWord().compareTo(p) > 0) {
        				
    					// Anade el par frequencia al final de la subsecuencia
        				seqPSF.add(new Pair_S_F(doc_id, freq));
        				// Anade el par palabra en el siguiente item de la secuencia recorrida
    					((List<Pair_W_SeqPSF>) index).insert(counterMain + 1,new Pair_W_SeqPSF(p, seqPSF));
    					
    				// Si "p" es menor a la palabra en secuencia, se insterta si es la ultima palabra en secuencia
    				}else if(currentWPair.getWord().compareTo(p) < 0 & !iteratorMain.hasNext()) {
    					seqPSF.add(new Pair_S_F(doc_id, freq));
    					((List<Pair_W_SeqPSF>) index).insert(counterMain,new Pair_W_SeqPSF(p, seqPSF));
    				}
    			}
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
		iteratorMain.reset();
		counter = 0;
    	
    	while(iteratorMain.hasNext()) {
    		Pair_W_SeqPSF currentWPair;
    		
    		counter++;
    		currentWPair = iteratorMain.getNext(); 
    		
    		// Compruebo que la palabra de la secuencia tenga el prefix indicado
    		if(currentWPair.getWord().startsWith(prefix)) {
    			((List<Pair_W_SeqPSF>) auxIndex).insert(counter, currentWPair);
    		}
    	}
    	
    	return auxIndex.iterator();
    }
}
