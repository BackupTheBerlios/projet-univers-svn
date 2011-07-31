package editor.view;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Rectangle;

public class Model extends Figure
{
    public Model()
    {
	layout = new XYLayout();
	setLayoutManager(layout);

	name.setForegroundColor(ColorConstants.blue);
	add(name);
	setConstraint(name,new Rectangle(5,5,-1,-1));

	setForegroundColor(ColorConstants.black);
	setBorder(new LineBorder(5));
    }
 
    public void setName(String name)
    {
	this.name.setText(name);	
    }
    
    /// ??
    private XYLayout layout;
    
    /// The structure
    private Label name = new Label();
}
