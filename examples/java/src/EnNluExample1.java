import tencent.ai.texsmart.*;

public class EnNluExample1 {
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
	
		System.out.println("=== Parse a piece of English text ===");
		String text = "John Smith stayed in San Francisco last month.";
		NluOutput output = engine.parseText(text);
	
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
			String typeStr = String.format("(%s,%s,%d,%s)", ent.type.name, ent.type.i18n, ent.type.flag, ent.type.path);
			System.out.printf("\t%s\t(%d,%d)\t%s\t%s\n", ent.str, ent.offset, ent.len, typeStr, ent.meaning);
		}
	}
}
