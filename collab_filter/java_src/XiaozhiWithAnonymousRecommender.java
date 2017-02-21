
import java.io.IOException;
import java.util.List;

import org.apache.mahout.cf.taste.common.TasteException;
import org.apache.mahout.cf.taste.impl.model.GenericUserPreferenceArray;
import org.apache.mahout.cf.taste.impl.model.PlusAnonymousUserDataModel;
import org.apache.mahout.cf.taste.impl.model.file.FileDataModel;
import org.apache.mahout.cf.taste.model.DataModel;
import org.apache.mahout.cf.taste.model.PreferenceArray;
import org.apache.mahout.cf.taste.recommender.RecommendedItem;

public class XiaozhiWithAnonymousRecommender
    extends XiaozhiRecommender {

  private final PlusAnonymousUserDataModel plusAnonymousModel;

  public XiaozhiWithAnonymousRecommender()
      throws TasteException, IOException {
    this(new FileDataModel(readResourceToTempFile("ratings.dat")));
  }

  public XiaozhiWithAnonymousRecommender(DataModel model) throws TasteException, IOException {
    super(new PlusAnonymousUserDataModel(model));
    plusAnonymousModel = (PlusAnonymousUserDataModel) getDataModel();
  }

  public synchronized List<RecommendedItem> recommend(PreferenceArray anonymousUserPrefs, int howMany)
      throws TasteException {
    plusAnonymousModel.setTempPrefs(anonymousUserPrefs);
    List<RecommendedItem> recommendations = recommend(PlusAnonymousUserDataModel.TEMP_USER_ID, howMany, null);
    plusAnonymousModel.clearTempPrefs();
    return recommendations;
  }

  public static String XiaozhiRecomend2(String arg) {
    System.out.println(arg);
    return arg;
  }

  public static String XiaozhiRecommend(String[] args) throws Exception {
  //public static String XiaozhiRecommend(String[] args) throws Exception {
  //public static void main(String[] args) throws Exception {

    PreferenceArray anonymousPrefs = new GenericUserPreferenceArray(3);

    anonymousPrefs.setUserID(0, PlusAnonymousUserDataModel.TEMP_USER_ID);
    //anonymousPrefs.setItemID(0, 20590);
    //anonymousPrefs.setValue(0, 3.0f);
    //anonymousPrefs.setItemID(1, 98925);
    //anonymousPrefs.setValue(1, 5.0f);
    //anonymousPrefs.setItemID(2, 8587);
    //anonymousPrefs.setValue(2, 2.0f);

    if (args != null) {
      if ((args.length == 6) || (args.length == 4) || (args.length == 2)) {
        for (int i = 0; i < args.length; i += 2) {
          anonymousPrefs.setItemID(i / 2, Integer.parseInt(args[i]));
          anonymousPrefs.setValue(i / 2, Float.parseFloat(args[i + 1]));
        }

        XiaozhiWithAnonymousRecommender recommender = new XiaozhiWithAnonymousRecommender();

        List<RecommendedItem> recommendations = recommender.recommend(anonymousPrefs, 3);

        if (recommendations.isEmpty()) {
          return null;
        }
        else {
          System.out.println(recommendations);
          return recommendations.toString();
        }
      }
      else {
        return null;
      }
    }
    else {
      return null;
    }
  }
}