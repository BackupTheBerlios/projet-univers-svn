package editor.view;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Rectangle;

/// An Object view
public class Object extends Figure
{

    public Object()
    {
	layout = new XYLayout();
	setLayoutManager(layout);

	name.setForegroundColor(ColorConstants.blue);
	add(name);
	Rectangle rectangle = new Rectangle(5,5,-1,-1); 
	setConstraint(name,rectangle);
	
	setForegroundColor(ColorConstants.darkGray);
	setBorder(new LineBorder(1));
	setOpaque(true);
    }
 
    public void setName(String name)
    {
	this.name.setText(name);	
    }

    public void setLayout(Rectangle rectangle) 
    {
	getParent().setConstraint(this,rectangle);
    }    
    
    /// ??
    private XYLayout layout;
    
    /// The structure
    private Label name = new Label();
}
