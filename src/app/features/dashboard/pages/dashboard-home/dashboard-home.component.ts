import {
  ChangeDetectionStrategy,
  Component,
  inject,
} from '@angular/core';

import { AsyncPipe } from '@angular/common';
import { map } from 'rxjs';

import { DashboardService } from '../../../../core/services/dashboard.service';
import { GreetingHeaderComponent } from '../../../../shared/components/greeting-header/greeting-header.component';
import { BalanceCardComponent } from '../../../../shared/components/balance-card/balance-card.component';
import { QuickActionsComponent } from '../../../../shared/components/quick-actions/quick-actions.component';
import { RecentActivityListComponent } from '../../../../shared/components/recent-activity-list/recent-activity-list.component';
import { FloatingActionComponent } from '../../../../shared/components/floating-action/floating-action.component';

@Component({
  selector: 'app-dashboard-home',
  standalone: true,
  imports: [
    AsyncPipe,
    GreetingHeaderComponent,
    BalanceCardComponent,
    QuickActionsComponent,
    RecentActivityListComponent,
    FloatingActionComponent,
  ],
  templateUrl: './dashboard-home.component.html',
  styleUrl: './dashboard-home.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class DashboardHomeComponent {
  private dashboardService = inject(DashboardService);

  readonly dashboard$ = this.dashboardService.getDashboardData();

  readonly trackByTransaction = (_: number, item: any) => item.id;
}
