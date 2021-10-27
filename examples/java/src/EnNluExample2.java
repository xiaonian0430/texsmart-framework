import tencent.ai.texsmart.*;

public class EnNluExample2 {
    public static void main(String[] args) {
    	String userDir = System.getProperty("user.dir");
		String dataDir = args.length >= 1 ? args[0] : userDir + "/../../data/nlu/kb/";
		//if(args.length < 1) {
		//	System.out.println("Please specify the data folder for the NLU engine");
		//	return;
		//}
	
		System.out.println("Creating and initializing the NLU engine...");
		NluEngine engine = new NluEngine();
		int workerCount = 4;
		boolean ret = engine.init(dataDir, workerCount);
		if(!ret) {
			System.out.println("Failed to initialize the engine");
			return;
		}

		String options = "{\"ner\":{\"enable\":true,\"fine_grained\":false}}";
		System.out.printf("Options: %s\n", options);

    	System.out.println("=== Parse a piece of English text ===");
    	//String text = "The history of natural language processing generally started in the 1950s.";
    	String text = "John Smith stayed in San Francisco last month.";
    	NluOutput output = engine.parseText(text, options);

    	System.out.printf("Input text: %s\n", text);
    	System.out.printf("Output norm text: %s\n", output.normText());
    	
    	System.out.println("Word-level segmentation results:");
		for(NluOutput.Term word : output.words()) {
			System.out.printf("\t%s\t(%d,%d)\t%s\n", word.str, word.offset, word.len, word.tag);
		}

		System.out.println("Phrase-level segmentation results:");
		for(NluOutput.Term phrase : output.phrases()) {
			System.out.printf("\t%s\t(%d,%d)\t%s\n", phrase.str, phrase.offset, phrase.len, phrase.tag);
		}
	
		System.out.println("NER results:");
		for(NluOutput.Entity ent : output.entities()) {
			System.out.printf("\t%s\t(%d,%d)\t%s\t%s\n", ent.str, ent.offset, ent.len, ent.type.name, ent.meaning);
		}
    }
}
