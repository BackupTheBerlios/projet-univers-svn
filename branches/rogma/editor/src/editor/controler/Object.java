package editor.controler;

import java.util.List;

import org.eclipse.draw2d.IFigure;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;

/// Controler for Object
public class Object extends AbstractGraphicalEditPart
{

    @Override
    protected IFigure createFigure()
    {
        IFigure figure = new editor.view.Object();
        return figure;
    }

    @Override
    protected void createEditPolicies()
    {
	// TODO Auto-generated method stub

    }

    @Override
    protected void refreshVisuals()
    {
        editor.view.Object figure = (editor.view.Object)getFigure();
        editor.model.Object model = (editor.model.Object)getModel();

        figure.setName(model.getName());
        figure.setLayout(model.getLayout());   
    }

    @Override
    protected List<java.lang.Object> getModelChildren()
    {
	editor.model.Object model = (editor.model.Object)getModel() ;
	return model.getChildren();
    }

}
