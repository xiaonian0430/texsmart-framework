import tencent.ai.texsmart.*;

public class ChsMatchingExample1 {
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

		System.out.println("=== Text Matching ===");
		String text1 = "我非常喜欢这只小狗";
		String text2 = "我很爱这条狗";
		TextMatchingOutput output = engine.matchText(text1, text2);
		if(output == null || output.size() < 1) {
			System.out.printf("Error occurred in text matching\n");
			return;
		}

		System.out.printf("Text-1: %s\nText-2: %s\nMatching score: %f\n",
				text1, text2, output.scoreAt(0));
	}
}
