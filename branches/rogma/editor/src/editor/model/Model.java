package editor.model;

import java.util.ArrayList;
import java.util.List;

public class Model
{
    public Model(String name)
    {
	this.name = name;
    }
    
    public void addChild(Object child)
    {
	children.add(child);
	child.setParent(this);
    }
    
    public String getName()
    {
	return name;
    }

    public List<Object> getChildren()
    {
	return children;
    }
    
    private String name ;
    private List<Object> children = new ArrayList<Object>();
}
