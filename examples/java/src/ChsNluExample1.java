import tencent.ai.texsmart.*;

public class ChsNluExample1 {
	public static void main(String[] args) {
		String userDir = System.getProperty("user.dir");
		String dataDir = args.length >= 1 ? args[0] : userDir + "/../../data/nlu/kb/";

		System.out.println("Creating and initializing the NLU engine...");
		NluEngine engine = new NluEngine();
		int workerCount = 4;
		boolean ret = engine.init(dataDir, workerCount);
		if(!ret) {
			System.out.println("Failed to initialize the engine");
			return;
		}

		System.out.println("=== 解析一个中文句子 ===");
		String text = "上个月30号，南昌王先生在自己家里边看流浪地球边吃煲仔饭";
		NluOutput output = engine.parseText(text);

		System.out.println("细粒度分词:");
		for(NluOutput.Term word : output.words()) {
			System.out.printf("\t%s\t(%d,%d)\t%s\n", word.str, word.offset, word.len, word.tag);
		}
	
		System.out.println("粗粒度分词:");
		for(NluOutput.Term phrase : output.phrases()) {
			System.out.printf("\t%s\t(%d,%d)\t%s\n", phrase.str, phrase.offset, phrase.len, phrase.tag);
		}

		System.out.println("命名实体识别（NER）:");
		for(NluOutput.Entity ent : output.entities()) {
			String typeStr = String.format("(%s,%s,%d,%s)", ent.type.name, ent.type.i18n, ent.type.flag, ent.type.path);
			System.out.printf("\t%s\t(%d,%d)\t%s\t%s\n", ent.str, ent.offset, ent.len, typeStr, ent.meaning);
		}
	}
}
