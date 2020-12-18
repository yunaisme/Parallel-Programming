package wordcount;
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.KeyValueTextInputFormat;

public class WordCount {

  public static class TokenizerMapper1
       extends Mapper<Object, Text, Text, LongWritable>{
    private final static LongWritable one = new LongWritable(1);
    private Text word = new Text();
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        word.set(itr.nextToken());
        context.write(word, one);
      }
    }
  }

  public static class LongSumReducer1
       extends Reducer<Text,LongWritable,Text,LongWritable> {
    private LongWritable result = new LongWritable();
    public void reduce(Text key, Iterable<LongWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (LongWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }
  
  public static class TokenizerMapper2
  		extends Mapper<Text, Text, LongWritable, Text>{
    private Text word = new Text();
    private long value_long;
    private LongWritable value_longW = new LongWritable();
    public void map(Text key, Text value, Context context
    				  ) throws IOException, InterruptedException {
    		value_long = Long.parseLong(value.toString());
    		value_longW.set(-value_long);
    		context.write(value_longW,key);
    	}
    }
    
  public static class LongSumReducer2
    	extends Reducer<LongWritable,Text,Text,LongWritable> {
    private long value_l;
    private LongWritable value_lW = new LongWritable();
    public void reduce(LongWritable value, Iterable<Text> words, Context context
                    	  ) throws IOException, InterruptedException {
    	   	for (Text word : words) {
    	   		value_l = (-1)*value.get();
        		value_lW.set(value_l);
        		context.write(word,value_lW);
    	   	}    	    
    	}
    }
    
    public static void main(String[] args) throws Exception {
    Configuration conf1 = new Configuration();
    Job job1 = Job.getInstance(conf1, "wordcount");
    job1.setJarByClass(WordCount.class);
    job1.setMapperClass(TokenizerMapper1.class);
    job1.setReducerClass(LongSumReducer1.class);
    job1.setOutputKeyClass(Text.class);
    job1.setOutputValueClass(LongWritable.class);
    job1.setOutputFormatClass(TextOutputFormat.class);
    FileInputFormat.addInputPath(job1, new Path(args[0]));
    FileOutputFormat.setOutputPath(job1, new Path(args[1]));
    job1.waitForCompletion(true);
    
    Configuration conf2 = new Configuration();
    Job job2 = Job.getInstance(conf2, "wordcount2");
    job2.setJarByClass(WordCount.class);
    job2.setMapperClass(TokenizerMapper2.class);
    job2.setReducerClass(LongSumReducer2.class);
    job2.setInputFormatClass(KeyValueTextInputFormat.class);
    FileInputFormat.addInputPath(job2, new Path(args[1]));
    FileOutputFormat.setOutputPath(job2, new Path(args[2]));
    job2.waitForCompletion(true);
    System.out.println("success");
  	}
}
