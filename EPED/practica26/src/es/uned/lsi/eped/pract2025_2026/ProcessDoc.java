package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.IteratorIF;

/* Un objeto de esta clase permite contabilizar la frecuencia
 * de las palabras de un documento.
 */
public class ProcessDoc {
    String doc_id;
    Seq_PSF words;

    /* Constructor */
    public ProcessDoc(String did) {
        this.doc_id = did;
        this.words = new Seq_PSF();
    }

    /* Devuelve la secuencia de pares <palabra,frecuencia> */
    public Seq_PSF getSequence() {
        return this.words;
    }

    /* Incrementa en 1 la frecuencia de la palabra w en el documento */    
    public void addWord(String w) {
        IteratorIF<Pair_S_F> iterator;
        boolean found;
        
        iterator = this.words.iterator();
        found = false;
        
        if (iterator != null) {
            while(iterator.hasNext()) {
            	Pair_S_F pair;
            	
            	pair = iterator.getNext();
            	
            	if(pair.getString().equals(w)) {
            		pair.incFrequency();
            		found = true;
            	}
            	if (!iterator.hasNext() & !found) {
            		this.words.add(new Pair_S_F(w, 1));
            		found = true;
            	}
            }
        } else {
            this.words.add(new Pair_S_F(w, 1));
        }
    }
}
