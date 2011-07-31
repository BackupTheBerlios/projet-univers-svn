package editor;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;
import org.eclipse.zest.core.widgets.Graph;
import org.eclipse.zest.core.widgets.GraphConnection;
import org.eclipse.zest.core.widgets.GraphNode;
import org.eclipse.zest.core.widgets.ZestStyles;
import org.eclipse.zest.layouts.algorithms.TreeLayoutAlgorithm;
import org.eclipse.zest.core.widgets.GraphContainer;

public class View extends ViewPart
{
    public static final String ID = "pu.view";

    public void createPartControl(Composite parent)
    {
	// Graph will hold all other objects
	graph = new Graph(parent, SWT.NONE);
	GraphContainer object1 = new GraphContainer(graph,SWT.NONE) ; 
	new GraphNode(object1, SWT.NONE,"Positionable");
	object1.open(false);
	object1.setText("#1");

	GraphContainer object2 = new GraphContainer(graph,SWT.NONE) ; 
	new GraphNode(object2, SWT.NONE,"Positionable");
	object2.open(false) ;
	object2.setText("#1");

	new GraphConnection(graph,ZestStyles.CONNECTIONS_DIRECTED,object1,object2);
	
	GraphContainer object3 = new GraphContainer(graph,SWT.NONE) ; 
	new GraphNode(object3, SWT.NONE,"Positionable");
	object3.open(false) ;
	object3.setText("#1");

	new GraphConnection(graph,ZestStyles.CONNECTIONS_DIRECTED,object1,object3);

	GraphContainer object4 = new GraphContainer(graph,SWT.NONE) ; 
	object4.open(false);
	object4.setText("#4");
	
	TreeLayoutAlgorithm algorithm = new TreeLayoutAlgorithm() ;
	graph.setLayoutAlgorithm(algorithm,true);
	
	// Selection listener on graphConnect or GraphNode is not supported
	// see https://bugs.eclipse.org/bugs/show_bug.cgi?id=236528
	graph.addSelectionListener(new SelectionAdapter()
	{
	    @Override
	    public void widgetSelected(SelectionEvent e)
	    {
		System.out.println(e);
	    }

	});
    }


    /**
     * Passing the focus request to the viewer's control.
     */
    public void setFocus()
    {
    }

    private Graph graph;
}
