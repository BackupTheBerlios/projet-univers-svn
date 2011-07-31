package editor;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.DefaultEditDomain;
import org.eclipse.gef.GraphicalViewer;
import org.eclipse.gef.ui.parts.GraphicalEditor;

import editor.model.Model;
import editor.model.Object;

/**
 * Basic class for editor, probably the view 
 * 
 * @author mroger
 * 
 */
public class Editor extends GraphicalEditor
{

    public static final String ID = "pu.editor";

    public Editor()
    {
	setEditDomain(new DefaultEditDomain(this));
    }


    @Override
    protected void configureGraphicalViewer()
    {
        super.configureGraphicalViewer();   
        GraphicalViewer viewer = getGraphicalViewer();
        viewer.setEditPartFactory(new ControlerFactory());
    }

    @Override
    public void doSave(IProgressMonitor monitor)
    {
	// TODO Auto-generated method stub
    }

    /// Startup initialisation
    @Override
    protected void initializeGraphicalViewer()
    {
        GraphicalViewer viewer = getGraphicalViewer();
        viewer.setContents(createTestContent());     
    }


    private Model createTestContent()
    {
	Model model = new Model("Test") ;
	Object o1 = new Object("#1") ;
	o1.setLayout(new Rectangle(30,30,100,50)) ;
	Object o2 = new Object("#2") ;
	o2.setLayout(new Rectangle(30,100,100,50)) ;
	model.addChild(o1) ;
	model.addChild(o2) ;
	
	return model;
    }

    
}
