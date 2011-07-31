package editor.controler;

import java.util.List;

import org.eclipse.draw2d.IFigure;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;

public class Model extends AbstractGraphicalEditPart
{

    @Override
    protected IFigure createFigure()
    {
        IFigure figure = new editor.view.Model();
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
        editor.view.Model figure = (editor.view.Model)getFigure();
        editor.model.Model model = (editor.model.Model)getModel();

        figure.setName(model.getName());
    }

    @Override
    protected List<editor.model.Object> getModelChildren()
    {
	editor.model.Model model = (editor.model.Model)getModel() ;
	return model.getChildren();
    }
    
}
