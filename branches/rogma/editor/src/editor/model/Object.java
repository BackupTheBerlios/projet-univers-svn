package editor.model;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;

/// Represent an Object model
public class Object
{
    public Object(String name)
    {
	this.name = name;
    }
    
    public void addChild(Object child)
    {
	children.add(child);
	child.setParent(this);
    }

    public void setParent(java.lang.Object parent)
    {
	this.parent = parent;
    }
    
    public String getName()
    {
	return name;
    }

    public List<java.lang.Object> getChildren()
    {
	return children;
    }

    public Rectangle getLayout()
    {
	return layout;
    }
    
    public void setLayout(Rectangle newLayout)
    {
	this.layout = newLayout;
    }
    
    private String name ;
    private List<java.lang.Object> children = new ArrayList<java.lang.Object>();
    private java.lang.Object parent = null;
    private Rectangle layout = new Rectangle();
}
