[System.Serializable]
public struct MyStruct {
    public int x;
    public float y;
    public override string ToString()
    {
        return string.Format("({0}, {1})", x, y);
    }
}

public class TestSyncListStruct : TestSyncListBase<MyStruct> {
    override protected MyStruct GetRandom()
    {
        MyStruct res = new MyStruct();
        res.x = UnityEngine.Random.Range(1, 42);
        res.y = UnityEngine.Random.Range(1.0f, 42.0f);
        return res;
    }
}
